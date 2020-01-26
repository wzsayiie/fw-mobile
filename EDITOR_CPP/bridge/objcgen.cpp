#include "objcgen.hh"
#include "langcoder.hh"

//==== ==== ==== ==== ==== assist ==== ==== ==== ==== ====

static string initial_capital(const string &word) {
    string ret = word;
    
    if (!ret.empty() && islower(ret[0])) {
        ret[0] = ret[0] - ('a' - 'A');
    }
    
    return ret;
}

//==== ==== ==== ==== ==== objc types ==== ==== ==== ==== ====

static string type_string(const string &pre, _type type, bool gap) {
    string ret;
    switch (type.iden) {
        case _type_id_null  : ret = "void"   ; break;
        case _type_id_bool  : ret = "BOOL"   ; break;
        case _type_id_int8  : ret = "int8_t" ; break;
        case _type_id_int16 : ret = "int16_t"; break;
        case _type_id_int32 : ret = "int32_t"; break;
        case _type_id_int64 : ret = "int64_t"; break;
        case _type_id_float : ret = "float"  ; break;
        case _type_id_double: ret = "double" ; break;
        
        case _type_id_string: ret = "NSString *"; break;
        case _type_id_bytes : ret = "NSMutableString *"; break;
        
        case _type_id_cls   : ret = pre + type.name + " *"; break;
        
        default:;
    }
    
    if (gap && ret.back() != '*') {
        ret.append(" ");
    }
    
    return ret;
}

static string type_string_n(const string &p, _type t) {return type_string(p, t, false);}
static string type_string_s(const string &p, _type t) {return type_string(p, t, true );}

//==== ==== ==== ==== ==== objc_coder ==== ==== ==== ==== ====

struct objc_coder : lang_coder {
    bool on_loop(const string &name, string *text) override;
    bool on_flag(const string &name, string *text) override;
    
    virtual bool on_loop_cls();
    virtual bool on_loop_func(vector<func_desc> *list);
    
    virtual void on_flag_header (string *text);
    virtual void on_flag_need   (string *text);
    virtual void on_flag_class  (string *text);
    virtual void on_flag_objccls(string *text);
    virtual void on_flag_cret   (string *text);
    virtual void on_flag_cfunc  (string *text);
    virtual void on_flag_cparams(string *text);
    virtual void on_flag_memret (string *text);
    virtual void on_flag_memfunc(string *text);
    
    virtual void set_meta(const meta_info &meta);
    
private:
    meta_info _meta;
    
    vector<cls_desc> *_cls_list = nullptr;
    int _cls_iter = 0;
    
    vector<func_desc> *_func_list = nullptr;
    int _func_iter = 0;
};

bool objc_coder::on_loop(const string &name, string *text) {
    /**/ if (name == "loop_class"  ) {return on_loop_cls();}
    else if (name == "loop_static" ) {return on_loop_func(&_cls_list->at(_cls_iter).cls_fs);}
    else if (name == "loop_virtual") {return on_loop_func(&_cls_list->at(_cls_iter).obj_fs);}
    
    return false;
}

bool objc_coder::on_loop_cls() {
    if (_cls_list == nullptr) {
        //iterate begin.
        if (_meta.cls_list.size() > 0) {
            _cls_list = &_meta.cls_list;
            _cls_iter = 0;
            return true;
        } else {
            return false;
        }
        
    } else if (_cls_iter + 1 < _cls_list->size()) {
        //iterate continue.
        _cls_iter += 1;
        return true;
        
    } else {
        //iterate end.
        _cls_list = nullptr;
        _cls_iter = 0;
        return false;
    }
}

bool objc_coder::on_loop_func(vector<func_desc> *list) {
    if (_func_list == nullptr) {
        //iterate begin.
        if (list->size() > 0) {
            _func_list = list;
            _func_iter = 0;
            return true;
        } else {
            return false;
        }
        
    } else if (_func_iter + 1 < _func_list->size()) {
        //iterate continue.
        _func_iter += 1;
        return true;
        
    } else {
        //iterate end.
        _func_list = nullptr;
        _func_iter = 0;
        return false;
    }
}

bool objc_coder::on_flag(const string &name, string *text) {
    /**/ if (name == "header" ) {on_flag_header (text);}
    else if (name == "need"   ) {on_flag_need   (text);}
    else if (name == "class"  ) {on_flag_class  (text);}
    else if (name == "objccls") {on_flag_objccls(text);}
    else if (name == "cret"   ) {on_flag_cret   (text);}
    else if (name == "cfunc"  ) {on_flag_cfunc  (text);}
    else if (name == "cparams") {on_flag_cparams(text);}
    else if (name == "memret" ) {on_flag_memret (text);}
    else if (name == "memfunc") {on_flag_memfunc(text);}
    
    return true;
}

void objc_coder::on_flag_header(string *text) {
    *text = file_name_of(_meta.objc_header);
}

void objc_coder::on_flag_need(string *text) {
    if (_meta.type == local_lib) {
        *text = "//NOTE: developer need to implement these functions:\n";
    }
}

void objc_coder::on_flag_class(string *text) {
    *text = _cls_list->at(_cls_iter).type.name;
}

void objc_coder::on_flag_objccls(string *text) {
    *text = _meta.objc_prefix + _cls_list->at(_cls_iter).type.name;
}

void objc_coder::on_flag_cret(string *text) {
    _type type = _func_list->at(_func_iter).retv;
    
    *text = type_string_s(_meta.objc_prefix, type);
}

void objc_coder::on_flag_cfunc(string *text) {
    *text = _func_list->at(_func_iter).name;
}

void objc_coder::on_flag_cparams(string *text) {
    auto &params = _func_list->at(_func_iter).params;
    
    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it != params.begin()) {
            text->append(", ");
        }
        text->append(type_string_s(_meta.objc_prefix, it->type));
        text->append(it->name);
    }
}

void objc_coder::on_flag_memret(string *text) {
    _type type = _func_list->at(_func_iter).retv;
    
    *text = type_string_n(_meta.objc_prefix, type);
}

void objc_coder::on_flag_memfunc(string *text) {
    auto &name   = _func_list->at(_func_iter).name;
    auto &params = _func_list->at(_func_iter).params;
    
    //function name.
    text->append(name);
    
    //first parameter.
    if (params.size() > 0) {
        param_desc first = params.front();
        
        string upper = initial_capital(first.name);
        if (!end_with(upper, name)) {
            text->append("With");
            text->append(upper);
        }
        text->append(":(");
        text->append(type_string_n(_meta.objc_prefix, first.type));
        text->append(")");
        text->append(first.name);
    }
    
    //followed parameters.
    if (params.size() <= 1) {
        return;
    }
    for (auto it = params.begin() + 1; it != params.end(); ++it) {
        text->append(" ");
        text->append(it->name);
        text->append(":(");
        text->append(type_string_n(_meta.objc_prefix, it->type));
        text->append(")");
        text->append(it->name);
    }
}

void objc_coder::set_meta(const meta_info &meta) {
    _meta = meta;
}

//==== ==== ==== ==== ==== generator ==== ==== ==== ==== ====

#include "objcform.hh"

void objc_gen_header(const meta_info &meta, bool to_stdout) {
    
    auto coder = make_shared<objc_coder>();
    coder->set_meta(meta);
    
    string text = coder->process(intf_header);
    
    if (to_stdout) {
        ii("===== objc header =====\n%s", text.c_str());
    } else {
        //
    }
}

void objc_gen_source(const meta_info &meta, bool to_stdout) {
}
