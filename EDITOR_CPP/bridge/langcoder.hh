#pragma once

#include "metapicker.hh"

enum string_block_type {
    type_text,
    type_flag,
    type_loop,
};

struct string_block {
    
    string_block(string_block_type t): type(t) {}
    
    string_block_type type;
    
    string value;
    vector<string_block *> kids;
};

struct lang_coder {
    
    virtual string process(const string &form, const meta_info &meta);
    
    virtual void handle_block     (string_block *block, string *added);
    virtual void handle_text_block(string_block *block, string *added);
    virtual void handle_flag_block(string_block *block, string *added);
    virtual void handle_loop_block(string_block *block, string *added);
    
    virtual void on_begin_cls();
    virtual void on_end_cls();
    
    virtual void on_begin_cls_func();
    virtual void on_end_cls_func();
    
    virtual void on_begin_obj_func();
    virtual void on_end_obj_func();
    
    virtual bool is_on_cls();
    virtual bool is_on_cls_func();
    virtual bool is_on_obj_func();
    
    virtual const meta_info &get_meta();
    virtual cls_desc *current_cls();
    virtual func_desc *current_func();
    
    virtual void on_flag(const string &name, string *out);
    
private:
    meta_info _meta;
    
    cls_desc  *_current_cls      = nullptr;
    func_desc *_current_cls_func = nullptr;
    func_desc *_current_obj_func = nullptr;
};
