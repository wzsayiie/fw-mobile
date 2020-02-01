#include "cppgen.hh"
#include "langcoder.hh"

static string ret_type_string(const std::string &prefix, _type type) {
    switch (type.iden) {
        case _type_id_null  : return "void"   ;
        case _type_id_bool  : return "bool"   ;
        case _type_id_int8  : return "int8_t" ;
        case _type_id_int16 : return "int16_t";
        case _type_id_int32 : return "int32_t";
        case _type_id_int64 : return "int64_t";
        case _type_id_float : return "float"  ;
        case _type_id_double: return "double" ;
        case _type_id_string: return "std::string";
        case _type_id_bytes : return "std::vector<uint8_t>";
        case _type_id_cls   : return prefix + type.name + "Ref";
        
        default: return "";
    }
}

static string param_type_string(const std::string &prefix, _type type) {
    switch (type.iden) {
        case _type_id_null  : return "void "   ;
        case _type_id_bool  : return "bool "   ;
        case _type_id_int8  : return "int8_t " ;
        case _type_id_int16 : return "int16_t ";
        case _type_id_int32 : return "int32_t ";
        case _type_id_int64 : return "int64_t ";
        case _type_id_float : return "float "  ;
        case _type_id_double: return "double " ;
        case _type_id_string: return "const std::string &";
        case _type_id_bytes : return "const std::vector<uint8_t> &";
        case _type_id_cls   : return prefix + type.name + "Ref ";
        
        default: return "";
    }
}

struct cpp_coder : lang_coder {
    void on_flag(const string &name, string *out) override;
    
    virtual void on_flag_header(string *out);
    virtual void on_flag_need  (string *out);
    virtual void on_flag_class (string *out);
    virtual void on_flag_cppcls(string *out);
    virtual void on_flag_ret   (string *out);
    virtual void on_flag_func  (string *out);
    virtual void on_flag_params(string *out);
};

void cpp_coder::on_flag(const string &name, string *out) {
    /**/ if (name == "header") {on_flag_header(out);}
    else if (name == "need"  ) {on_flag_need  (out);}
    else if (name == "class" ) {on_flag_class (out);}
    else if (name == "cppcls") {on_flag_cppcls(out);}
    else if (name == "ret"   ) {on_flag_ret   (out);}
    else if (name == "func"  ) {on_flag_func  (out);}
    else if (name == "params") {on_flag_params(out);}
}

void cpp_coder::on_flag_header(string *out) {
    auto &header = get_meta().cpp_header;
    
    *out = file_name_of(header);
}

void cpp_coder::on_flag_need(string *out) {
    target_lib_type lib_type = get_meta().lib_type;
    
    if (lib_type == cpp_lib) {
        *out = "//NOTE: developer need to implement these functions:\n";
    }
}

void cpp_coder::on_flag_class(string *out) {
    *out = current_cls()->type.name;
}

void cpp_coder::on_flag_cppcls(string *out) {
    auto &prefix = get_meta().cpp_prefix;
    auto &cls_name = current_cls()->type.name;
    
    *out = prefix + cls_name;
}

void cpp_coder::on_flag_ret(string *out) {
    auto &prefix = get_meta().cpp_prefix;
    auto &type = current_func()->retv;
    
    *out = ret_type_string(prefix, type);
}

void cpp_coder::on_flag_func(string *out) {
    *out = current_func()->name;
}

void cpp_coder::on_flag_params(string *text) {
    auto &params = current_func()->params;
    auto &prefix = get_meta().cpp_prefix;
    
    for (auto it = params.begin(); it != params.end(); ++it) {
        if (it != params.begin()) {
            text->append(", ");
        }
        text->append(param_type_string(prefix, it->type));
        text->append(it->name);
    }
}

#include "cppform.hh"

void cpp_gen_header(const meta_info &meta) {
    
    auto coder = make_shared<cpp_coder>();
    string text = coder->process(F_HEADER, meta);
    
    ii("===== cpp header =====");
    ii("%s", text.c_str());
}

void cpp_gen_source(const meta_info &meta, bool to_stdout) {
}
