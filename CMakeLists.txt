cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

project(noahh-sdk VERSION 0.2.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} INTERFACE)

target_compile_definitions(${PROJECT_NAME} INTERFACE -DPROJECT_NAME=${CMAKE_PROJECT_NAME})

set(NOAHH_CODEGEN_PATH ${CMAKE_CURRENT_BINARY_DIR}/codegenned)
set(NOAHH_BIN_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(NOAHH_LOADER_PATH ${CMAKE_CURRENT_SOURCE_DIR}/loader)

include(cmake/NoahhFile.cmake)
include(cmake/Platform.cmake)

target_sources(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/entry.cpp)


add_subdirectory(codegen)

add_custom_target(CodegenRun ALL
	COMMAND Codegen ${NOAHH_TARGET_PLATFORM} bindings ${NOAHH_CODEGEN_PATH}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	COMMENT "Run Codegen"
	BYPRODUCTS ${NOAHH_CODEGEN_PATH}/GeneratedSource.cpp
)
add_dependencies(${PROJECT_NAME} CodegenRun)
add_dependencies(CodegenRun Codegen)

# Hacky way to supress the not generated error
if (NOT EXISTS ${NOAHH_CODEGEN_PATH}/GeneratedSource.cpp)
	make_directory(${NOAHH_CODEGEN_PATH})
	execute_process(COMMAND touch ${NOAHH_CODEGEN_PATH}/GeneratedSource.cpp)
endif()

target_sources(${PROJECT_NAME} INTERFACE ${NOAHH_CODEGEN_PATH}/GeneratedSource.cpp)
target_include_directories(${PROJECT_NAME} INTERFACE ${NOAHH_CODEGEN_PATH}/..)

target_include_directories(${PROJECT_NAME} INTERFACE
	${NOAHH_LOADER_PATH}/include
	${NOAHH_LOADER_PATH}/include/Noahh/cocos/
	${NOAHH_LOADER_PATH}/include/Noahh/cocos/cocos2dx
	${NOAHH_LOADER_PATH}/include/Noahh/cocos/cocos2dx/include
	${NOAHH_LOADER_PATH}/include/Noahh/cocos/cocos2dx/support/zip_support
	${NOAHH_LOADER_PATH}/include/NOAHH/cocos/cocos2dx/kazmath/include
	${NOAHH_LOADER_PATH}/include/Noahh/cocos/extensions
	${NOAHH_LOADER_PATH}/include/Noahh/fmod
)
target_link_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/loader/include/link)

add_subdirectory(filesystem)
add_subdirectory(fmt)

target_link_libraries(${PROJECT_NAME} INTERFACE filesystem fmt)



if (NOT EXISTS ${NOAHH_BIN_PATH})
	make_directory(${NOAHH_BIN_PATH})
endif()

if (NOAHH_LINK_SOURCE)
	set(NOAHH_PLATFORM_BIN_PATH ${NOAHH_BIN_PATH}/nightly/${NOAHH_PLATFORM_BINARY})
else()
	set(NOAHH_PLATFORM_BIN_PATH ${NOAHH_BIN_PATH}/${PROJECT_VERSION}/${NOAHH_PLATFORM_BINARY})
endif()


if (PROJECT_IS_TOP_LEVEL)
	add_subdirectory(loader)
	target_link_libraries(${PROJECT_NAME} INTERFACE noahh-loader)
elseif(EXISTS ${NOAHH_PLATFORM_BIN_PATH})
	target_link_libraries(${PROJECT_NAME} INTERFACE "${NOAHH_PLATFORM_BIN_PATH}")
	target_precompile_headers(${PROJECT_NAME} INTERFACE "${NOAHH_LOADER_PATH}/include/Noahh/Noahh.hpp")
else()
	message(FATAL_ERROR "No valid loader binary to link to! Install a pre-built binary for version ${PROJECT_VERSION} with Noahh CLI or build it from source.")
endif()