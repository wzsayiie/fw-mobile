#include "cqdata.hh"
#include "cqdata_base64.hh"

cq_member(cqData) {
    std::vector<uint8_t> vector;
};

cqDataRef cqData::createWithData(cqDataRef that) {
    cqDataRef object = cqData::create();
    if (that != nullptr) {
        object->dat->vector = that->dat->vector;
    }
    return object;
}

cqDataRef cqData::createWithBytes(const void *bytes, size_t size) {
    cqDataRef object = cqData::create();
    if (bytes != nullptr && size > 0) {
        auto ptr = (const uint8_t *)bytes;
        object->dat->vector.assign(ptr, ptr + size);
    }
    return object;
}

cqDataRef cqData::createWithContentsOfFile(const std::string &path) {
    cqDataRef object = cqData::create();
    
    if (path.empty()) {
        return object;
    }
    
    FILE *file = fopen(path.c_str(), "rb");
    if (file == nullptr) {
        return object;
    }
    while (true) {
        uint8_t buffer[1024];
        size_t size = fread(buffer, 1, sizeof(buffer), file);
        object->dat->vector.assign(buffer, buffer + size);
        if (size < sizeof(buffer)) {
            break;
        }
    }
    fclose(file);
    
    return object;
}

cqDataRef cqData::createWithBase64EncodedData(const std::string &encoded) {
    cqDataRef object = cqData::create();
    object->dat->vector = cqBase64::decode(encoded);
    return object;
}

const std::vector<uint8_t> &cqData::data() {
    return dat->vector;
}

const void *cqData::bytes() {
    return dat->vector.data();
}

size_t cqData::size() {
    return dat->vector.size();
}

bool cqData::writeToFile(const std::string &path) {
    if (path.empty()) {
        return false;
    }
    
    FILE *file = fopen(path.c_str(), "wb");
    if (file == nullptr) {
        return false;
    }
    fwrite(dat->vector.data(), 1, dat->vector.size(), file);
    fclose(file);
    
    return true;
}

std::string cqData::base64EncodedString() {
    return cqBase64::from(dat->vector.data(), dat->vector.size());
}
