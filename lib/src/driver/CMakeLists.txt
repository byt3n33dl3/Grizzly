cmake_minimum_required(VERSION 3.8)

project("mydriver" C)
set(MYDRIVER_VERSION "1.0")

set(KERNEL_DIR "/lib/modules/${CMAKE_HOST_SYSTEM_VERSION}/build")

function(lkm_add_driver)
    cmake_parse_arguments(LKM "" "NAME" "" ${ARGN})

    if(NOT LKM_NAME)
        return()
    else()
        string(TOLOWER ${LKM_NAME} MODULE_NAME)
    endif()

    set(KBUILD_COMMAND ${CMAKE_MAKE_PROGRAM} -C ${KERNEL_DIR} M=${CMAKE_BINARY_DIR} src=${CMAKE_SOURCE_DIR})
    set(KBUILD_FILE_PATH "${CMAKE_SOURCE_DIR}/Kbuild")

    if(EXISTS ${KBUILD_FILE_PATH})
        file(REMOVE ${KBUILD_FILE_PATH})
    endif()

    foreach(MODULE_SOURCE_FILE ${LKM_UNPARSED_ARGUMENTS})
        get_filename_component(SOURCE_FILE ${MODULE_SOURCE_FILE} NAME_WE)
        file(APPEND ${KBUILD_FILE_PATH} "${MODULE_NAME}-m += ${SOURCE_FILE}.o\n")
    endforeach()

    file(APPEND ${KBUILD_FILE_PATH} "obj-m += ${MODULE_NAME}.o\n")
    file(APPEND ${KBUILD_FILE_PATH} "ccflags-y := -Wframe-larger-than=65535\n")

    if(SECURE)
        file(APPEND ${KBUILD_FILE_PATH} "ccflags-y += -DSECURE\n")
    endif()

    set(MODULE_BIN_FILE "${CMAKE_BINARY_DIR}/${MODULE_NAME}.ko")
    
    add_custom_target(
        ${MODULE_NAME}
        ALL COMMAND ${KBUILD_COMMAND} modules
        COMMENT "Compiling Linux Kernel Module: ${MODULE_BIN_FILE}"
    )
    
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${KBUILD_FILE_PATH} ${CMAKE_BINARY_DIR})
endfunction()

lkm_add_driver(
    NAME mydriver
    module.c
    handlers.c
)