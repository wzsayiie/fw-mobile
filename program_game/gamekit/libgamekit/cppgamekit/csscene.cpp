#include "csscene.hh"

cq_member(csScene) {
    std::string name;
};

void csScene::setName(const std::string &name) {
    dat->name = name;
}

std::string csScene::name() {
    return dat->name;
}
