cmake_minimum_required(VERSION 3.3.0)

add_library(proxy_loader SHARED proxyLoader.c)
set_target_properties(proxy_loader PROPERTIES
	OUTPUT_NAME "XInput9_1_0"
	RUNTIME_OUTPUT_DIRECTORY "${NOAHH_BIN_PATH}"
)

add_custom_command(
	COMMAND 
		${CMAKE_COMMAND} -E rename "$<TARGET_FILE:proxy_loader>" "${NOAHH_BIN_PATH}/nightly/$<TARGET_FILE_NAME:proxy_loader>"
	DEPENDS $<TARGET_FILE:proxy_loader>
	VERBATIM
	TARGET proxy_loader
)