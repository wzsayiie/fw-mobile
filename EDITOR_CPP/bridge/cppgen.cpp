#include "cppgen.hh"
#include "langcoder.hh"

//==== ==== ==== ==== ==== c++ types ==== ==== ==== ==== ====

static string ret_type_string(const std::string &pre, _type type) {
    switch (type.iden) {
        case _type_id_null   : return "void"   ;
        case _type_id_bool   : return "bool"   ;
        case _type_id_int8   : return "int8_t" ;
        case _type_id_int16  : return "int16_t";
        case _type_id_int32  : return "int32_t";
        case _type_id_int64  : return "int64_t";
        case _type_id_float  : return "float"  ;
        case _type_id_double : return "double" ;
        
        case _type_id_string : return "std::string";
        case _type_id_bytes  : return "std::vector<uint8_t>";
        
        case _type_id_cls    : return pre + type.name + "Ref";
        case _type_id_loc_cls: return pre + type.name + "Ref";
        case _type_id_cpp_cls: return pre + type.name + "Ref";
        
        default: return "";
    }
}

static string param_type_string(const std::string &pre, _type type) {
    switch (type.iden) {
        case _type_id_null   : return "void "   ;
        case _type_id_bool   : return "bool "   ;
        case _type_id_int8   : return "int8_t " ;
        case _type_id_int16  : return "int16_t ";
        case _type_id_int32  : return "int32_t ";
        case _type_id_int64  : return "int64_t ";
        case _type_id_float  : return "float "  ;
        case _type_id_double : return "double " ;
        
        case _type_id_string : return "const std::string &";
        case _type_id_bytes  : return "const std::vector<uint8_t> &";
        
        case _type_id_cls    : return pre + type.name + "Ref ";
        case _type_id_loc_cls: return pre + type.name + "Ref ";
        case _type_id_cpp_cls: return pre + type.name + "Ref ";
        
        default: return "";
    }
}

//==== ==== ==== ==== ==== cpp_coder ==== ==== ==== ==== ====

struct cpp_coder : lang_coder {
    bool on_loop(const string &name, string *text) override;
    bool on_flag(const string &name, string *text) override;
    
    virtual bool on_loop_cls();
    virtual bool on_loop_func(vector<func_desc> *list);
    
    virtual void on_flag_header(string *text);
    virtual void on_flag_need  (string *text);
    virtual void on_flag_class (string *text);
    virtual void on_flag_cppcls(string *text);
    virtual void on_flag_ret   (string *text);
    virtual void on_flag_func  (string *text);
    virtual void on_flag_params(string *text);
    
    virtual void set_meta(const meta_info &meta);
    
private:
    meta_info _meta;
    
    vector<cls_desc> *_cls_list = nullptr;
    int _cls_iter = 0;
    
    vector<func_desc> *_func_list = nullptr;
    int _func_iter = 0;
};

bool cpp_coder::on_loop(const string &name, string *text) {
    /**/ if (name == "loop_class"  ) {return on_loop_cls();}
    else if (name == "loop_static" ) {return on_loop_func(&_cls_list->at(_cls_iter).cls_fs);}
    else if (name == "loop_virtual") {return on_loop_func(&_cls_list->at(_cls_iter).obj_fs);}
    
    return false;
}

bool cpp_coder::on_loop_cls() {
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

bool cpp_coder::on_loop_func(vector<func_desc> *list) {
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

bool cpp_coder::on_flag(const string &name, string *text) {
    /**/ if (name == "header") {on_flag_header(text);}
    else if (name == "need"  ) {on_flag_need  (text);}
    else if (name == "class" ) {on_flag_class (text);}
    else if (name == "cppcls") {on_flag_cppcls(text);}
    else if (name == "ret"   ) {on_flag_ret   (text);}
    else if (name == "func"  ) {on_flag_func  (text);}
    else if (name == "params") {on_flag_params(text);}
    
    return true;
}

void cpp_coder::on_flag_header(string *text) {
    *text = file_name_of(_meta.cpp_header);
}

void cpp_coder::on_flag_need(string *text) {
    *text = "//NOTE: developer need to implement these functions:\n";
}

void cpp_coder::on_flag_class(string *text) {
    *text = _cls_list->at(_cls_iter).type.name;
}

void cpp_coder::on_flag_cppcls(string *text) {
    *text = _meta.cpp_prefix + _cls_list->at(_cls_iter).type.name;
}

void cpp_coder::on_flag_ret(string *text) {
    _type type = _func_list->at(_func_iter).retv;
    
    *text = ret_type_string(_meta.cpp_prefix, type);
}

void cpp_coder::on_flag_func(string *text) {
    *text = _func_list->at(_func_iter).name;
}

void cpp_coder::on_flag_params(string *text) {
    auto &params = _func_list->at(_func_iter).params;
    
    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it != params.begin()) {
            text->append(", ");
        }
        text->append(param_type_string(_meta.cpp_prefix, it->type));
        text->append(it->name);
    }
}

void cpp_coder::set_meta(const meta_info &meta) {
    _meta = meta;
}

//==== ==== ==== ==== ==== generator ==== ==== ==== ==== ====

#include "cppform.hh"

void cpp_gen_header(const meta_info &meta, bool to_stdout) {
    
    auto coder = make_shared<cpp_coder>();
    coder->set_meta(meta);
    
    string text = coder->process(intf_header);
    
    if (to_stdout) {
        ii("===== cpp header =====\n%s", text.c_str());
    } else {
        //
    }
}

void cpp_gen_source(const meta_info &meta, bool to_stdout) {
}
