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

    if(NOAHH_CLI STREQUAL "NOAHH_CLI-NOTFOUND")
        message(WARNING "create_noahh_file called, but Noahh CLI was not found - You will need to manually package the .noahh files")
    else()

        add_custom_target(${proname}_PACKAGE ALL
            DEPENDS ${proname}
            COMMAND ${NOAHH_CLI} pkg ${CMAKE_CURRENT_SOURCE_DIR} $<TARGET_FILE_DIR:${proname}> $<TARGET_FILE_DIR:${proname}>/${proname}.noahh --install --cached
            VERBATIM USES_TERMINAL
        )
    endif()

endfunction()