#include "langcoder.hh"

static bool is_blank(char c) {
    if (c == ' ' ) {return true;}
    if (c == '\t') {return true;}
    if (c == '\r') {return true;}
    if (c == '\n') {return true;}

    return false;
}

static bool is_word_letter(char c) {
    if ('a' <= c && c <= 'z') {return true;}
    if ('A' <= c && c <= 'Z') {return true;}
    if ('0' <= c && c <= '9') {return true;}
    if (/*.......*/ c == '_') {return true;}

    return false;
}

static int check_text(const char *ptr, const char *end, string *text) {
    if (*ptr == '$') {
        return 0;
    }
    
    while (ptr < end && *ptr != '$') {
        text->append(1, *ptr);
        ptr += 1;
    }
    
    return (int)text->size();
}

static int check_flag(const char *ptr, const char *end, string *flag) {
    if (*ptr != '$') {
        return 0;
    }
    
    const char *begin = ptr;
    
    //flag is like '$(xxx)'.
    if (ptr + 2 < end && ptr[1] == '(') {
        ptr += 2; //skip "$(".
        
        while (ptr < end && *ptr != ')') {
            flag->append(1, *ptr);
            ptr += 1;
        }
        if (ptr < end && *ptr == ')') {
            //skip ')'.
            ptr += 1;
        }
    }
    //flag is like '$xxx'.
    else {
        ptr += 1; //skip "$".
        
        while (ptr < end && is_word_letter(*ptr)) {
            flag->append(1, *ptr);
            ptr += 1;
        }
    }
    
    //ignore a newline.
    if (ptr < end && *ptr == '\n') {
        ptr += 1;
    }
    
    return (int)(ptr - begin);
}

static string_block *read_text_block(const char **ptr, const char *end) {
    string text;
    int len = check_text(*ptr, end, &text);
    
    if (len > 0) {
        *ptr += len;
        
        auto block = new string_block(type_text);
        block->value = text;
        return block;
        
    } else {
        return nullptr;
    }
}

static string_block *read_flag_block(const char **ptr, const char *end) {
    string flag;
    int len = check_flag(*ptr, end, &flag);
    
    if (len > 0 && !start_with("loop_", flag)) {
        *ptr += len;
        
        auto block = new string_block(type_flag);
        block->value = flag;
        return block;
        
    } else {
        return nullptr;
    }
}

static string_block *read_block(const char **ptr, const char *end);

static string_block *read_loop_block(const char **ptr, const char *end) {
    string flag;
    int len = check_flag(*ptr, end, &flag);
    
    //lopp struct starts with "loop_xxx".
    if (len <= 0 || !start_with("loop_", flag)) {
        return nullptr;
    }
    
    *ptr += len;
    
    auto block = new string_block(type_loop);
    block->value = flag;
    
    while (*ptr < end) {
        string_block *kid = read_block(ptr, end);
        
        //loop structure ends with "end".
        if (kid->type == type_flag && kid->value == "end") {
            delete kid;
            break;
        }
        
        block->kids.push_back(kid);
    }
    
    return block;
}

static string_block *read_block(const char **ptr, const char *end) {
    
    string_block *block = read_loop_block(ptr, end);
    if (block != nullptr) {
        return block;
    }
    
    block = read_flag_block(ptr, end);
    if (block != nullptr) {
        return block;
    }
    
    return read_text_block(ptr, end);
}

static void delete_blocks(vector<string_block *> *blocks) {
    if (blocks->empty()) {
        return;
    }
    
    for (auto &it : *blocks) {
        delete_blocks(&it->kids);
        delete it;
    }
    blocks->clear();
}

string lang_coder::process(const string &form, const meta_info &meta) {
    
    _meta = meta;
    
    const char *ptr = form.c_str();
    const char *end = form.c_str() + form.size();
    
    //skip leading whitespace.
    while (ptr < end && is_blank(*ptr)) {
        ptr += 1;
    }
    
    //structuring.
    vector<string_block *> blocks;
    while (ptr < end) {
        string_block *it = read_block(&ptr, end);
        blocks.push_back(it);
    }
    
    //to string.
    string added;
    for (auto it : blocks) {
        handle_block(it, &added);
    }
    
    delete_blocks(&blocks);
    
    return added;
}

void lang_coder::handle_block(string_block *block, string *added) {
    switch (block->type) {
        case type_text: handle_text_block(block, added); break;
        case type_flag: handle_flag_block(block, added); break;
        case type_loop: handle_loop_block(block, added); break;
        default:;
    }
}

void lang_coder::handle_text_block(string_block *block, string *added) {
    added->append(block->value);
}

void lang_coder::handle_flag_block(string_block *block, string *added) {
    string text;
    on_flag(block->value, &text);
    
    added->append(text);
}

void lang_coder::handle_loop_block(string_block *block, string *added) {
    if (block->value == "loop_cls") {
        
        if (_meta.cls_list.empty()) {
            return;
        }
        for (auto &cls : _meta.cls_list) {
            _current_cls = &cls;
            on_begin_cls();
            
            for (auto &it : block->kids) {
                handle_block(it, added);
            }
            
            on_end_cls();
            _current_cls = nullptr;
        }
        
    } else if (block->value == "loop_cls_func") {
        
        if (_current_cls == nullptr) {
            return;
        }
        for (auto &func : _current_cls->cls_fs) {
            _current_cls_func = &func;
            on_begin_cls_func();
            
            for (auto &it : block->kids) {
                handle_block(it, added);
            }
            
            on_end_cls_func();
            _current_cls_func = nullptr;
        }
        
    } else if (block->value == "loop_obj_func") {
        
        if (_current_cls == nullptr) {
            return;
        }
        for (auto &func : _current_cls->obj_fs) {
            _current_obj_func = &func;
            on_begin_obj_func();
            
            for (auto &it : block->kids) {
                handle_block(it, added);
            }
            
            on_end_obj_func();
            _current_obj_func = nullptr;
        }
    }
}

void lang_coder::on_begin_cls() {}
void lang_coder::on_end_cls  () {}

void lang_coder::on_begin_cls_func() {}
void lang_coder::on_end_cls_func  () {}

void lang_coder::on_begin_obj_func() {}
void lang_coder::on_end_obj_func  () {}

bool lang_coder::is_on_cls     () {return _current_cls      != nullptr;}
bool lang_coder::is_on_cls_func() {return _current_cls_func != nullptr;}
bool lang_coder::is_on_obj_func() {return _current_obj_func != nullptr;}

const meta_info &lang_coder::get_meta() {
    return _meta;
}

cls_desc *lang_coder::current_cls() {
    return _current_cls;
}

func_desc *lang_coder::current_func() {
    if (_current_cls_func != nullptr) {
        return _current_cls_func;
    } else {
        return _current_obj_func;
    }
}

void lang_coder::on_flag(const string &name, string *out) {
}
