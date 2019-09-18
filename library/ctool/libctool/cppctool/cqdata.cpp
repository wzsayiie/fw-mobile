#include "cqdata.hh"

bool cqData::readFile(const std::string &path, std::vector<uint8_t> *data) {
    if (path.empty() || data == nullptr) {
        return false;
    }
    
    FILE *file = fopen(path.c_str(), "rb");
    if (file == nullptr) {
        return false;
    }
    
    data->clear();
    while (!feof(file)) {
        uint8_t buffer[1024 * 4];
        size_t size = fread(buffer, 1, sizeof(buffer), file);
        data->insert(data->end(), buffer, buffer + size);
    }
    fclose(file);
    return true;
}

bool cqData::readFile(const std::string &path, std::string *string) {
    if (path.empty() || string == nullptr) {
        return false;
    }
    
    std::vector<uint8_t> data;
    if (!readFile(path, &data)) {
        return false;
    }
    
    string->assign((char *)data.data(), data.size());
    return true;
}

bool cqData::_writeFile(const std::string &path, uint8_t *bytes, int length) {
    if (path.empty()) {
        return false;
    }
    
    FILE *file = fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return false;
    }
    
    if (bytes != nullptr && length > 0) {
        fwrite(bytes, 1, (size_t)length, file);
    } else {
        //NOTE: don't write, make the file empty.
    }
    fclose(file);
    return true;
}
