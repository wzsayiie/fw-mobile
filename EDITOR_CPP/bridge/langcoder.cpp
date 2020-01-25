#include "langcoder.hh"

//==== ==== ==== ==== ==== block type ==== ==== ==== ==== ====

enum block_type {
    type_text,
    type_flag,
    type_loop,
};

struct a_block {
    virtual block_type type() = 0;
    virtual ~a_block() {}
};

struct text_block: a_block    {block_type type(){return type_text;} string text;};
struct flag_block: a_block    {block_type type(){return type_flag;} string flag;};
struct loop_block: flag_block {block_type type(){return type_loop;} vector<shared_ptr<a_block>> kids;};

//==== ==== ==== ==== ==== check text or flag ==== ==== ==== ==== ====

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

//==== ==== ==== ==== ==== read block ==== ==== ==== ==== ====

static shared_ptr<a_block> read_block(const char **ptr, const char *end);

static shared_ptr<text_block> try_read_text(const char **ptr, const char *end) {
    string text;
    int len = check_text(*ptr, end, &text);
    
    if (len > 0) {
        *ptr += len;
        
        auto block = make_shared<text_block>();
        block->text = text;
        return block;
    } else {
        return nullptr;
    }
}

static shared_ptr<flag_block> try_read_flag(const char **ptr, const char *end) {
    string flag;
    int len = check_flag(*ptr, end, &flag);
    
    if (len > 0 && !start_with("loop_", flag)) {
        *ptr += len;
        
        auto block = make_shared<flag_block>();
        block->flag = flag;
        return block;
    } else {
        return nullptr;
    }
}

static shared_ptr<loop_block> try_read_loop(const char **ptr, const char *end) {
    string flag;
    int len = check_flag(*ptr, end, &flag);
    
    //lopp struct starts with "loop_xxx".
    if (len <= 0 || !start_with("loop_", flag)) {
        return nullptr;
    }
    
    *ptr += len;
    
    auto block = make_shared<loop_block>();
    block->flag = flag;
    
    while (*ptr < end) {
        shared_ptr<a_block> kid = read_block(ptr, end);
        
        //loop structure ends with "end".
        if (kid->type() == type_flag) {
            auto a = static_pointer_cast<flag_block>(kid);
            if (a->flag == "end") {
                break;
            }
        }
        
        block->kids.push_back(kid);
    }
    
    return block;
}

static shared_ptr<a_block> read_block(const char **ptr, const char *end) {
    
    shared_ptr<a_block> block = try_read_loop(ptr, end);
    if (block != nullptr) {
        return block;
    }
    
    block = try_read_flag(ptr, end);
    if (block != nullptr) {
        return block;
    }
    
    return try_read_text(ptr, end);
}

//==== ==== ==== ==== ==== build string ==== ==== ==== ==== ====

static void string_block(lang_coder *coder, shared_ptr<a_block> a, string *add);

static void string_text(lang_coder *coder, shared_ptr<text_block> block, string *add) {
    add->append(block->text);
}

static void string_flag(lang_coder *coder, shared_ptr<flag_block> block, string *add) {
    string out;
    bool okay = coder->on_flag(block->flag, &out);
    
    if (okay) {
        add->append(out);
    }
}

static void string_loop(lang_coder *coder, shared_ptr<loop_block> block, string *add) {
    while (true) {
        bool again = coder->on_loop(block->flag, nullptr);
        if (!again) {
            break;
        }
        
        for (auto it : block->kids) {
            string_block(coder, it, add);
        }
    }
}

static void string_block(lang_coder *coder, shared_ptr<a_block> a, string *add) {
    switch (a->type()) {
        case type_text: string_text(coder, static_pointer_cast<text_block>(a), add); break;
        case type_flag: string_flag(coder, static_pointer_cast<flag_block>(a), add); break;
        case type_loop: string_loop(coder, static_pointer_cast<loop_block>(a), add); break;
        default:;
    }
}

//==== ==== ==== ==== ==== language coder ==== ==== ==== ==== ====

static bool is_blank(char c) {
    if (c == ' ' ) {return true;}
    if (c == '\t') {return true;}
    if (c == '\r') {return true;}
    if (c == '\n') {return true;}

    return false;
}

string lang_coder::process(const string &tl) {
    
    const char *ptr = tl.c_str();
    const char *end = tl.c_str() + tl.size();
    
    //skip leading whitespace.
    while (ptr < end && is_blank(*ptr)) {
        ptr += 1;
    }
    
    //structuring.
    vector<shared_ptr<a_block>> blocks;
    while (ptr < end) {
        shared_ptr<a_block> it = read_block(&ptr, end);
        blocks.push_back(it);
    }
    
    //to string.
    string add;
    for (auto it : blocks) {
        string_block(this, it, &add);
    }
    
    return add;
}
