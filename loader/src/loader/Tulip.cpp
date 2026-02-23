
#include <Noahh/loader/Tulip.hpp>

using namespace noahh::prelude;

Result<void*> noahh::hook::createWrapper(
    void* address,
    tulip::hook::WrapperMetadata const& metadata
) noexcept {
    return tulip::hook::createWrapper(address, metadata);
}

std::shared_ptr<tulip::hook::CallingConvention> noahh::hook::createConvention(
    tulip::hook::TulipConvention convention
) noexcept {
    return tulip::hook::createConvention(convention);
}

