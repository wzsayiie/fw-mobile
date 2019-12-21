#pragma once

#include "cqctoolbase.hh"

_CQCTOOL_BEGIN_VERSION_NS

namespace cq {

    enum value_type {
        type_null   ,
        type_bool   ,
        type_int64  ,
        type_double ,
        type_str    ,
        type_vector ,
        type_str_map,
        type_int_map,
    };

    struct _value_dat {
        value_type type = type_null;
        union {
            bool    a_bool  ;
            int64_t a_int64 ;
            double  a_double;
            void   *a_ptr   ;
        };
    };

    struct value {

        //construct:

        value();
        value(std::nullptr_t);
        value(bool    v);
        value(int8_t  v);
        value(int16_t v);
        value(int32_t v);
        value(int64_t v);
        value(float   v);
        value(double  v);

        //if $v is null, the value's type will be type_null.
        value(const char *v);

        value(const std::string                  &v);
        value(const std::vector<value>           &v);
        value(const std::map<std::string, value> &v);
        value(const std::map<int64_t, value>     &v);

        value(const value &v);

        //getter:

        value_type type() const;

        //if wanted type is different with actual type of value,
        //then the value will be regarded as duck type and be converted automatically.

        bool    get_bool  () const;
        int8_t  get_int8  () const;
        int16_t get_int16 () const;
        int32_t get_int32 () const;
        int64_t get_int64 () const;
        float   get_float () const;
        double  get_double() const;

        std::string                  get_str    () const;
        std::vector<value>           get_vector () const;
        std::map<std::string, value> get_str_map() const;
        std::map<int64_t    , value> get_int_map() const;

        //setter:

        const value &operator=(std::nullptr_t);
        const value &operator=(bool    v);
        const value &operator=(int8_t  v);
        const value &operator=(int16_t v);
        const value &operator=(int32_t v);
        const value &operator=(int64_t v);
        const value &operator=(float   v);
        const value &operator=(double  v);

        //if $v is null, the type will be converted to type_null.
        const value &operator=(const char *v);

        const value &operator=(const std::string                  &v);
        const value &operator=(const std::vector<value>           &v);
        const value &operator=(const std::map<std::string, value> &v);
        const value &operator=(const std::map<int64_t, value>     &v);

        const value &operator=(const value &v);

        //NOTE: as_vector(), as_str_map() and as_int_map() will change the value's type.
        
        std::vector<value>           &as_vector ();
        std::map<std::string, value> &as_str_map();
        std::map<int64_t    , value> &as_int_map();

        //NOTE: [] operator will change value'type to type_str_map.
        value &operator[](const std::string &k);

        //destruct:

        ~value();

    private:
        _value_dat dat;
    };

} //end of namespace cq

_CQCTOOL_END_VERSION_NS
