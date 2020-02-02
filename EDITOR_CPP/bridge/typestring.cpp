#include "typestring.hh"

string cpp_type_str(const meta_info &meta, _type type) {
    string prefix = meta.cpp_prefix;
    
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
        case _type_id_bytes : return "std::vector<uint8>";
        case _type_id_cls   : return prefix + type.name + "Ref";
        
        default: return "";
    }
}

string cpp_type_str_p(const meta_info &meta, _type type) {
    string prefix = meta.cpp_prefix;
    
    switch (type.iden) {
        case _type_id_null  : return "void"   ;
        case _type_id_bool  : return "bool"   ;
        case _type_id_int8  : return "int8_t" ;
        case _type_id_int16 : return "int16_t";
        case _type_id_int32 : return "int32_t";
        case _type_id_int64 : return "int64_t";
        case _type_id_float : return "float"  ;
        case _type_id_double: return "double" ;
        case _type_id_string: return "const std::string &";
        case _type_id_bytes : return "std::vector<uint8> &"; //mutable.
        case _type_id_cls   : return prefix + type.name + "Ref";
        
        default: return "";
    }
}

string objc_type_str(const meta_info &meta, _type type) {
    string prefix = meta.objc_prefix;
    
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
