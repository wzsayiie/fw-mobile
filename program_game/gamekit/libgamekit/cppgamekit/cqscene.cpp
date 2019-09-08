#include "cqscene.hh"

cq_member(cqScene) {
    std::string name;
};

void cqScene::setName(const std::string &name) {
    dat->name = name;
}

std::string cqScene::name() {
    return dat->name;
}
