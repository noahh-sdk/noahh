cmake_minimum_required(VERSION 3.21)


add_library(NoahhBootstrapper SHARED Bootstrapper.cpp)
target_compile_features(NoahhBootstrapper PUBLIC cxx_std_23)
set_target_properties(NoahhBootstrapper PROPERTIES
	PREFIX "" 
	OUTPUT_NAME "NoahhBootstrapper"
	LIBRARY_OUTPUT_DIRECTORY "${NOAHH_BIN_PATH}/nightly"
	RUNTIME_OUTPUT_DIRECTORY "${NOAHH_BIN_PATH}/nightly"
)

target_link_libraries(NoahhBootstrapper PRIVATE)

add_library(FakeNoahh SHARED FakeNoahh.cpp)
target_compile_features(FakeNoahh PUBLIC cxx_std_23)
set_target_properties(FakeNoahh PROPERTIES
	PREFIX "" 
	OUTPUT_NAME "Noahh"
)

set_target_properties(NoahhBootstrapper PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
set_target_properties(NoahhBootstrapper PROPERTIES INSTALL_RPATH "./")

set_target_properties(FakeNoahh PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
set_target_properties(FakeNoahh PROPERTIES INSTALL_RPATH "./")

target_link_libraries(NoahhBootstrapper PRIVATE FakeNoahh)

