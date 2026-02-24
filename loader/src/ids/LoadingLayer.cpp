#include <Noahh/modify/IDManager.hpp>
#include <Noahh/utils/NodeIDs.hpp>
#include <Noahh/binding/LoadingLayer.hpp>

using namespace noahh::prelude;
using namespace noahh::node_ids;

$register_ids(LoadingLayer) {
    setIDs(
        this, 0,
        "bg-texture",
        "gd-logo",
        "robtop-logo",
        "cocos2d-logo",
        "fmod-logo",
        "loading-text",
        "text-area",
        "progress-slider"
    );
}

