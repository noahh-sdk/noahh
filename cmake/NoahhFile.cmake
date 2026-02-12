if (NOT DEFINED NOAHH_CLI)
    find_program(NOAHH_CLI NAMES noahh.exe noahh-cli.exe noahh noahh-cli)
endif()

if (NOAHH_CLI STREQUAL "NOAHH_CLI-NOTFOUND")
	message(STATUS "Unable to find Noahh CLI")
else()
    message(STATUS "Found Noahh CLI: ${NOAHH_CLI}")
endif()

function(create_noahh_file proname)
    message(STATUS "Creating noahh file")

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mod.json ${CMAKE_CURRENT_BINARY_DIR}/what.txt)
    set_target_properties(${proname} PROPERTIES CMAKE_CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/mod.json)

    execute_process(
        COMMAND ${NOAHH_CLI} package get-id ${CMAKE_CURRENT_SOURCE_DIR} --raw
        OUTPUT_VARIABLE MOD_ID
    )

    set_target_properties(${proname} PROPERTIES PREFIX "")
    set_target_properties(${proname} PROPERTIES OUTPUT_NAME ${MOD_ID})

    if(NOAHH_CLI STREQUAL "NOAHH_CLI-NOTFOUND")
        message(WARNING "create_noahh_file called, but Noahh CLI was not found - You will need to manually package the .noahh files")
    else()
        add_custom_target(${proname}_PACKAGE ALL
            DEPENDS ${proname} ${CMAKE_CURRENT_SOURCE_DIR}/mod.json
            COMMAND ${NOAHH_CLI} package new ${CMAKE_CURRENT_SOURCE_DIR} --binary $<TARGET_FILE:${proname}> --output $<TARGET_FILE_DIR:${proname}>/${proname}.noahh --install
            VERBATIM USES_TERMINAL
        )
    endif()

endfunction()