include(cmake/PlatformDetect.cmake)

if (NOT ${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
	set(NOAHH_TARGET_PLATFORM ${NOAHH_TARGET_PLATFORM} PARENT_SCOPE)
endif()

if (NOAHH_TARGET_PLATFORM STREQUAL "iOS")
	# make sure that we get the ios sdk

	message(STATUS "iOS c++ compiler: ${CMAKE_CXX_COMPILER}")
	set(CMAKE_OSX_ARCHITECTURES arm64)
	if (NOT DEFINED CMAKE_OSX_SYSROOT OR CMAKE_OSX_SYSROOT STREQUAL "")
		if (NOT DEFINED NOAHH_IOS_SDK OR NOAHH_IOS_SDK STREQUAL "")
			execute_process(COMMAND xcrun --show-sdk-path --sdk iphoneos
			OUTPUT_VARIABLE NOAHH_IOS_SDK
				OUTPUT_STRIP_TRAILING_WHITESPACE
			)
		endif()

		set(CMAKE_OSX_SYSROOT ${NOAHH_IOS_SDK})
	else()
		set(NOAHH_IOS_SDK ${CMAKE_OSX_SYSROOT})
	endif()
	set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0")
	set(CMAKE_SYSTEM_NAME "iOS")

	message(STATUS "Using iOS SDK: ${NOAHH_IOS_SDK}")

	# this fails on ios builds
	set(BUILD_MD2HTML_EXECUTABLE "OFF")

	set_target_properties(${PROJECT_NAME} PROPERTIES
		SYSTEM_NAME iOS
		OSX_SYSROOT ${NOAHH_IOS_SDK}
		OSX_ARCHITECTURES arm64
	)

	target_link_libraries(${PROJECT_NAME} INTERFACE
		"-framework OpenGLES"       # needed for CCClippingNode reimpl and ScrollLayer
		"-framework UIKit"          # needed for file picking (UIApplication)
		"-framework Foundation"     # needed for many things
		"-framework AVFoundation"   # needed for microphone access
		"-framework CoreGraphics"   # needed for image saving
		"-framework GameController" # needed for controller input
	)

	target_compile_definitions(${PROJECT_NAME} INTERFACE
		-DGLES_SILENCE_DEPRECATION
	)

	set(NOAHH_OUTPUT_NAME "Noahh.ios")
	set(NOAHH_PLATFORM_BINARY "Noahh.ios.dylib")
	set(NOAHH_MOD_BINARY_SUFFIX ".ios.dylib" CACHE STRING "" FORCE)

	if (NOT ${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
		set(NOAHH_TARGET_PLATFORM_SHORT "ios" PARENT_SCOPE)
		# this is needed because else loading mods will fail below ios 14.5
		set(CMAKE_OSX_DEPLOYMENT_TARGET "14.0" PARENT_SCOPE)
	else()
		set(NOAHH_TARGET_PLATFORM_SHORT "ios")
	endif()
elseif (NOAHH_TARGET_PLATFORM STREQUAL "MacOS")
	set_target_properties(${PROJECT_NAME} PROPERTIES 
		SYSTEM_NAME MacOS
	)

	# for some reason, this value is initialized as an empty string by default. idk why
	if (NOT DEFINED CMAKE_OSX_ARCHITECTURES OR CMAKE_OSX_ARCHITECTURES STREQUAL "")
		set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
	endif()

	# only exists as a global property
	set(CMAKE_OSX_DEPLOYMENT_TARGET 11.0)

	target_link_libraries(${PROJECT_NAME} INTERFACE
		"-framework Cocoa"
		"-framework OpenGL"
		"-framework SystemConfiguration"
		${NOAHH_LOADER_PATH}/include/link/macos/libfmod.dylib
	)

	target_compile_definitions(${PROJECT_NAME} INTERFACE
		-DCommentType=CommentTypeDummy
		-DGL_SILENCE_DEPRECATION
	)

	set(NOAHH_OUTPUT_NAME "Noahh")
	set(NOAHH_PLATFORM_BINARY "Noahh.dylib")
	set(NOAHH_MOD_BINARY_SUFFIX ".dylib" CACHE STRING "" FORCE)

	if (NOT ${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
		set(NOAHH_TARGET_PLATFORM_SHORT "mac" PARENT_SCOPE)
	else()
		set(NOAHH_TARGET_PLATFORM_SHORT "mac")
	endif()
elseif (NOAHH_TARGET_PLATFORM STREQUAL "Win64")
	set_target_properties(${PROJECT_NAME} PROPERTIES
		SYSTEM_NAME Win64
		GENERATOR_PLATFORM x64
	)

	target_compile_definitions(${PROJECT_NAME} INTERFACE NOMINMAX)

	target_link_libraries(${PROJECT_NAME} INTERFACE 
		${NOAHH_LOADER_PATH}/include/link/win64/libcocos2d.lib
		${NOAHH_LOADER_PATH}/include/link/win64/libExtensions.lib
		${NOAHH_LOADER_PATH}/include/link/win64/glew32.lib
		${NOAHH_LOADER_PATH}/include/link/win64/fmod.lib
		opengl32
	)

	if (PROJECT_IS_TOP_LEVEL AND CMAKE_BUILD_TYPE STREQUAL "Debug")
		target_link_libraries(${PROJECT_NAME} INTERFACE
			${NOAHH_LOADER_PATH}/include/link/win64/gd-libcurl.lib
		)
	endif()

	# Windows links against .lib and not .dll
	set(NOAHH_OUTPUT_NAME "Noahh")
	set(NOAHH_PLATFORM_BINARY "Noahh.lib")
	set(NOAHH_MOD_BINARY_SUFFIX ".dll" CACHE STRING "" FORCE)

	if (NOT ${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
		set(NOAHH_TARGET_PLATFORM_SHORT "win" PARENT_SCOPE)
	else()
		set(NOAHH_TARGET_PLATFORM_SHORT "win")
	endif()
elseif (NOAHH_TARGET_PLATFORM STREQUAL "Android32")
	set_target_properties(${PROJECT_NAME} PROPERTIES
		SYSTEM_NAME Android
	)

	target_link_libraries(${PROJECT_NAME} INTERFACE
		c
		unwind
		${NOAHH_LOADER_PATH}/include/link/android32/libcocos2dcpp.so
		${NOAHH_LOADER_PATH}/include/link/android32/libfmod.so
		GLESv2
		log
	)

	set(NOAHH_OUTPUT_NAME "Noahh.android32")
	set(NOAHH_PLATFORM_BINARY "Noahh.android32.so")
	set(NOAHH_MOD_BINARY_SUFFIX ".android32.so" CACHE STRING "" FORCE)

	if (NOT ${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
		set(NOAHH_TARGET_PLATFORM_SHORT "android32" PARENT_SCOPE)
	else()
		set(NOAHH_TARGET_PLATFORM_SHORT "android32")
	endif()
elseif (NOAHH_TARGET_PLATFORM STREQUAL "Android64")
	set_target_properties(${PROJECT_NAME} PROPERTIES
		SYSTEM_NAME Android
	)

	target_link_libraries(${PROJECT_NAME} INTERFACE
		c
		unwind
		${NOAHH_LOADER_PATH}/include/link/android64/libcocos2dcpp.so
		${NOAHH_LOADER_PATH}/include/link/android64/libfmod.so
		GLESv2
		log
	)

	# this should help with fixing exceptions
	set(ANDROID_STL c++_shared)
	# a little desperate
	add_definitions(-DANDROID_STL=c++_shared)

	set(NOAHH_OUTPUT_NAME "Noahh.android64")
	set(NOAHH_PLATFORM_BINARY "Noahh.android64.so")
	set(NOAHH_MOD_BINARY_SUFFIX ".android64.so" CACHE STRING "" FORCE)

	if (NOT ${PROJECT_NAME} STREQUAL ${CMAKE_PROJECT_NAME})
		set(NOAHH_TARGET_PLATFORM_SHORT "android64" PARENT_SCOPE)
	else()
		set(NOAHH_TARGET_PLATFORM_SHORT "android64")
	endif()
else()
	message(FATAL_ERROR "Unknown platform ${NOAHH_TARGET_PLATFORM}")
endif()