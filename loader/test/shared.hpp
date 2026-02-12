#define EXPORT_NAME TestDependency
#include <Noahh/Noahh.hpp>

API_INIT("com.noahh.testdep")

class TestDependency {
public:
	static void depTest(GJGarageLayer* gl);
		// API_DECL(&TestDependency::depTest, gl);
};