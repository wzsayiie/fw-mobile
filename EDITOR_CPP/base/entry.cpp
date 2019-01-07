#include "entry.h"

//app args ->

static vector<string> *arg_list() {
    vector<string> *object = NULL;
    if (object == NULL) {
        object = new vector<string>;
    }
    return object;
}

void set_args(int argc, const char *argv[], int begin) {
    vector<string> *list = arg_list();
    
    list->clear();
    for (int it = begin; it < argc; ++it) {
        list->push_back(argv[it]);
    }
}

vector<string> get_args() {
    return *arg_list();
}

//app entry ->

struct entry_item {
    string name;
    string shortened;
    app_entry entry;
};

static vector<entry_item> *get_entry_list() {
    static vector<entry_item> *object = NULL;
    if (object == NULL) {
        object = new vector<entry_item>;
    }
    return object;
}

entry_setter::entry_setter(app_entry entry, const string &name, const string &shortened) {
    entry_item item;
    item.name = name;
    item.shortened = shortened;
    item.entry = entry;
    get_entry_list()->push_back(item);
}

app_entry get_entry(const string &name) {
    for (const auto &it : *get_entry_list()) {
        if (it.name == name || it.shortened == name) {
            return it.entry;
        }
    }
    return NULL;
}
