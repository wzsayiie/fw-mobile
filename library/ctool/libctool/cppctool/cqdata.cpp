#include "cqdata.hh"

bool readFromFile(const std::string &path, std::vector<uint8_t> *data) {
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

bool writeToFile(const std::string &path, const std::vector<uint8_t> &data) {
    if (path.empty()) {
        return false;
    }
    
    FILE *file = fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return false;
    }
    
    fwrite(data.data(), 1, data.size(), file);
    fclose(file);
    return true;
}
