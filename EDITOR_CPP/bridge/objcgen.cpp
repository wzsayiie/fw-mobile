#include "objcgen.hh"
#include "langcoder.hh"

static string initial_capital(const string &word) {
    string ret = word;
    
    if (!ret.empty() && islower(ret[0])) {
        ret[0] = ret[0] - ('a' - 'A');
    }
    
    return ret;
}

static string c_type_string(const string &prefix, _type type) {
    switch (type.iden) {
        case _type_id_null  : return "void "   ;
        case _type_id_bool  : return "BOOL "   ;
        case _type_id_int8  : return "int8_t " ;
        case _type_id_int16 : return "int16_t ";
        case _type_id_int32 : return "int32_t ";
        case _type_id_int64 : return "int64_t ";
        case _type_id_float : return "float "  ;
        case _type_id_double: return "double " ;
        case _type_id_string: return "NSString *";
        case _type_id_bytes : return "NSMutableString *";
        case _type_id_cls   : return prefix + type.name + " *";
        
        default: return "";
    }
}

static string objc_type_string(const string &prefix, _type type) {
    switch (type.iden) {
        case _type_id_null  : return "void"   ;
        case _type_id_bool  : return "BOOL"   ;
        case _type_id_int8  : return "int8_t" ;
        case _type_id_int16 : return "int16_t";
        case _type_id_int32 : return "int32_t";
        case _type_id_int64 : return "int64_t";
        case _type_id_float : return "float"  ;
        case _type_id_double: return "double" ;
        case _type_id_string: return "NSString *";
        case _type_id_bytes : return "NSMutableString *";
        case _type_id_cls   : return prefix + type.name + " *";
        
        default: return "";
    }
}

struct objc_coder : lang_coder {
    void on_flag(const string &name, string *out) override;
    
    virtual void on_flag_header  (string *out);
    virtual void on_flag_need    (string *out);
    virtual void on_flag_class   (string *out);
    virtual void on_flag_objccls (string *out);
    virtual void on_flag_cret    (string *out);
    virtual void on_flag_cfunc   (string *out);
    virtual void on_flag_cparams (string *out);
    virtual void on_flag_objcret (string *out);
    virtual void on_flag_objcfunc(string *out);
};

void objc_coder::on_flag(const string &name, string *out) {
    /**/ if (name == "header"  ) {on_flag_header  (out);}
    else if (name == "need"    ) {on_flag_need    (out);}
    else if (name == "class"   ) {on_flag_class   (out);}
    else if (name == "objccls" ) {on_flag_objccls (out);}
    else if (name == "cret"    ) {on_flag_cret    (out);}
    else if (name == "cfunc"   ) {on_flag_cfunc   (out);}
    else if (name == "cparams" ) {on_flag_cparams (out);}
    else if (name == "objcret" ) {on_flag_objcret (out);}
    else if (name == "objcfunc") {on_flag_objcfunc(out);}
}

void objc_coder::on_flag_header(string *out) {
    auto &header = get_meta().objc_header;
    
    *out = file_name_of(header);
}

void objc_coder::on_flag_need(string *out) {
    target_lib_type lib_type = get_meta().lib_type;
    
    if (lib_type == local_lib) {
        *out = "//NOTE: developer need to implement these functions:\n";
    }
}

void objc_coder::on_flag_class(string *out) {
    *out = current_cls()->type.name;
}

void objc_coder::on_flag_objccls(string *out) {
    auto &prefix = get_meta().objc_prefix;
    auto &cls_name = current_cls()->type.name;
    
    *out = prefix + cls_name;
}

void objc_coder::on_flag_cret(string *out) {
    auto &prefix = get_meta().objc_prefix;
    auto &type = current_func()->retv;
    
    *out = c_type_string(prefix, type);
}

void objc_coder::on_flag_cfunc(string *out) {
    *out = current_func()->name;
}

void objc_coder::on_flag_cparams(string *out) {
    auto &params = current_func()->params;
    auto &prefix = get_meta().objc_prefix;
    
    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it != params.begin()) {
            out->append(", ");
        }
        out->append(c_type_string(prefix, it->type));
        out->append(it->name);
    }
}

void objc_coder::on_flag_objcret(string *out) {
    auto &prefix = get_meta().objc_prefix;
    auto &type = current_func()->retv;
    
    *out = objc_type_string(prefix, type);
}

void objc_coder::on_flag_objcfunc(string *out) {
    auto &prefix = get_meta().objc_prefix;
    auto &name   = current_func()->name;
    auto &params = current_func()->params;
    
    //function name.
    out->append(name);
    
    //first parameter.
    if (params.size() > 0) {
        param_desc first = params.front();
        
        string upper = initial_capital(first.name);
        if (!end_with(upper, name)) {
            out->append("With");
            out->append(upper);
        }
        out->append(":(");
        out->append(objc_type_string(prefix, first.type));
        out->append(")");
        out->append(first.name);
    }
    
    //followed parameters.
    if (params.size() <= 1) {
        return;
    }
    for (auto it = params.begin() + 1; it != params.end(); ++it) {
        out->append(" ");
        out->append(it->name);
        out->append(":(");
        out->append(objc_type_string(prefix, it->type));
        out->append(")");
        out->append(it->name);
    }
}

#include "objcform.hh"

void objc_gen_header(const meta_info &meta) {
    
    auto coder = make_shared<objc_coder>();
    string text = coder->process(F_HEADER, meta);
    
    ii("===== objc header =====");
    ii("%s", text.c_str());
}

void objc_gen_source(const meta_info &meta) {
}
