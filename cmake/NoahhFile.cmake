if (NOT DEFINED NOAHH_CLI)
    find_program(NOAHH_CLI NAMES noahh.exe noahh-cli.exe noahh noahh-cli)
endif()

if (NOAHH_CLI STREQUAL "NOAHH_CLI-NOTFOUND")
	message(STATUS "Unable to find Noahh CLI")
else()
    message(STATUS "Found Noahh CLI: ${NOAHH_CLI}")
endif()

function(create_noahh_file proname)
    message(
        DEPRECATION
        "create_noahh_file has been deprecated, and will 
        be replaced by create_noahh_file_v2 in the future. 
        Do note that create_noahh_file_v2 will be *renamed* 
        to create_noahh_file"
    )

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

function(create_noahh_file_v2 proname)
    message(STATUS "Creating noahh file")

    if(NOAHH_CLI STREQUAL "NOAHH_CLI-NOTFOUND")
        message(WARNING "create_noahh_file called, but Noahh CLI was not found - You will need to manually package the .noahh files")
    else()

        add_custom_target(${proname}_PACKAGE ALL
            DEPENDS ${proname}
            COMMAND ${NOAHH_CLI} package new ${CMAKE_CURRENT_SOURCE_DIR} --out $<TARGET_FILE_DIR:${proname}>/${proname}.noahh --install
            VERBATIM USES_TERMINAL
        )
    endif()

endfunction()

function(package_noahh_resources proname src dest prefix)
    message(STATUS "Packaging resources from ${src} with prefix ${prefix} into ${dest}")

    if(NOAHH_CLI STREQUAL "NOAHH_CLI-NOTFOUND")
        message(WARNING "package_noahh_resources called, but Noahh CLI was not found - You will need to manually package the resources")
    else()

        add_custom_target(${proname}_PACKAGE ALL
            DEPENDS ${proname}
            COMMAND ${NOAHH_CLI} resources ${src} ${dest} --prefix ${prefix} --cached
            VERBATIM USES_TERMINAL
        )
    endif()
endfunction()