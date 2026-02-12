#include <Noahh/Noahh.hpp>

USE_NOAHH_NAMESPACE();

NOAHH_API bool NOAHH_CALL noahh_load(Mod*) {
	// Dispatcher::get()->addFunction<void(GJGarageLayer*)>("test-garage-open", [](GJGarageLayer* gl) {
	// 	auto label = CCLabelBMFont::create("Dispatcher works!", "bigFont.fnt");
	// 	label->setPosition(100, 80);
	// 	label->setScale(.4f);
	// 	label->setZOrder(99999);
	// 	gl->addChild(label);
	// });
	return true;
}