// included by default in every noahh project

#include <Noahh/Noahh.hpp>

NOAHH_API bool NOAHH_CALL noahh_implicit_load(noahh::Mod* m) {
	noahh::Interface::get()->init(m);
	return true;
}