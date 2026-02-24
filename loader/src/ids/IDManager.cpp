#include <Noahh/modify/IDManager.hpp>

using namespace noahh;

NodeIDs* NodeIDs::get() {
    static auto inst = new NodeIDs;
    return inst;
}

