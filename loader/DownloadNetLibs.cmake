if (NOAHH_TARGET_PLATFORM STREQUAL "iOS")
	set(net_libs_plat "ios")
	set(net_libs_hash "SHA256=425bf321b5c88ef91ebf5320ba648c068c23da78a282faf7885d8db443a415f7")
elseif (NOAHH_TARGET_PLATFORM STREQUAL "MacOS")
	set(net_libs_plat "macos")
	set(net_libs_hash "SHA256=02edf88355d7230f7d4845e4d02feba83b5d8f2fd7f03b2a7feb499fee8f3a78")
elseif (NOAHH_TARGET_PLATFORM STREQUAL "Win64")
	set(net_libs_plat "windows")
	set(net_libs_hash "SHA256=ad0694e39bc51104830925a8b9c45ad088e6e5cae28509f3ff39284f59f2912d")
elseif (NOAHH_TARGET_PLATFORM STREQUAL "Android32")
	set(net_libs_plat "android32")
	set(net_libs_hash "SHA256=6e74d1347fe88bf3c835ac4f2c9a1fe09c88d3dd260bd8aca2e247a97a0ebe13")
elseif (NOAHH_TARGET_PLATFORM STREQUAL "Android64")
	set(net_libs_plat "android64")
	set(net_libs_hash "SHA256=a87a9b97850bc07fbdb3e65619875d5aa3efede0694196e3a2dc2d6c7672004f")
endif()

set(net_libs_version "8.19.0-5")
CPMAddPackage(
	NAME net_libs_bin
	VERSION "${net_libs_version}_${net_libs_plat}"
	URL "https://github.com/noahh-sdk/net_libs/releases/download/v${net_libs_version}/curl-${net_libs_plat}.zip"
	URL_HASH ${net_libs_hash}
	DOWNLOAD_ONLY YES
)

target_include_directories(${PROJECT_NAME} PRIVATE ${net_libs_bin_SOURCE_DIR}/include)
if (WIN32)
	target_link_libraries(${PROJECT_NAME} 
		${net_libs_bin_SOURCE_DIR}/cares.lib
		${net_libs_bin_SOURCE_DIR}/libcurl.lib
		${net_libs_bin_SOURCE_DIR}/nghttp2.lib
		${net_libs_bin_SOURCE_DIR}/libcrypto.lib
		${net_libs_bin_SOURCE_DIR}/libssl.lib
		${net_libs_bin_SOURCE_DIR}/zs.lib
		${net_libs_bin_SOURCE_DIR}/zstd_static.lib
	)
else()
	target_link_libraries(${PROJECT_NAME}
		${net_libs_bin_SOURCE_DIR}/libcares.a
		${net_libs_bin_SOURCE_DIR}/libcurl.a
		${net_libs_bin_SOURCE_DIR}/libnghttp2.a
		${net_libs_bin_SOURCE_DIR}/libcrypto.a
		${net_libs_bin_SOURCE_DIR}/libssl.a
		${net_libs_bin_SOURCE_DIR}/libz.a
		${net_libs_bin_SOURCE_DIR}/libzstd.a
	)
endif()

CPMAddPackage("gh:noahh-sdk/net_libs#963652a")
target_link_libraries(${PROJECT_NAME} ca-bundle)

if (WIN32)
	set(ZLIB_LIBRARY "${net_libs_bin_SOURCE_DIR}/zs.lib")
else()
	set(ZLIB_LIBRARY "${net_libs_bin_SOURCE_DIR}/libz.a")
endif()

set(ZLIB_INCLUDE_DIR "${net_libs_bin_SOURCE_DIR}/include")