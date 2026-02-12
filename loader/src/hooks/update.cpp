#include <Noahh/Modify.hpp>
#include <InternalLoader.hpp>

USE_NOAHH_NAMESPACE();

class $modify(CCScheduler) {
    void update(float dt) {
        InternalLoader::get()->executeGDThreadQueue();
        return CCScheduler::update(dt);
    }
};