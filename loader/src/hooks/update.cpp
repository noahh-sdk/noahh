#include <loader/LoaderImpl.hpp>

using namespace noahh::prelude;

#include <Noahh/modify/CCScheduler.hpp>

struct FunctionQueue : Modify<FunctionQueue, CCScheduler> {
    void update(float dt) {
        LoaderImpl::get()->executeMainThreadQueue();
        return CCScheduler::update(dt);
    }
};

