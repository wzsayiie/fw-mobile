#import "cqstdex.hh"

string::string(NSString *that) : std::string(non_null(that.UTF8String)) {
}

const string &string::operator=(NSString *that) {
    assign(that.UTF8String ? that.UTF8String : "");
    return *this;
}

string::operator NSString *() const {
    return @(c_str());
}
