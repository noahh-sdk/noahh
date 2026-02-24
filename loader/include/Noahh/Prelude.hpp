#pragma once

// Because C++ doesn't like using
// namespaces that don't exist
namespace noahh {
    namespace addresser {}
    namespace cast {}
    namespace cocos {}
    namespace utils {}
    namespace helper {}
    namespace op {}
    namespace stream {}
    namespace view {}
    namespace async {}
}

namespace cocos2d {
    namespace extension {}
}

namespace noahh {
    namespace prelude {
        using namespace ::noahh;
        using namespace ::noahh::addresser;
        using namespace ::noahh::cast;
        using namespace ::noahh::cocos;
        using namespace ::noahh::helper;
        using namespace ::noahh::utils;
        using namespace ::noahh::op;
        using namespace ::noahh::stream;
        using namespace ::noahh::view;
        using namespace ::noahh::async;
        using namespace ::cocos2d;
        using namespace ::cocos2d::extension;
    }
}

