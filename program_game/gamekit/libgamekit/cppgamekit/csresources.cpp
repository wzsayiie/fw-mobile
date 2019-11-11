#include "csresources.hh"

static std::string sResourcesDirectory;

void csResources::setResourcesDirectory(const std::string &directory) {
    sResourcesDirectory = directory;
}
