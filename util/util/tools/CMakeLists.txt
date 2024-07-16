cmake_minimum_required(VERSION 3.12) 
set(CRONO_TARGET_NAME "xhptdc8_util")
project(${CRONO_TARGET_NAME})

# _____________________________________________________________________________________________________________________
# Build Windows/Linux library for (Debug/Release) configurations.
# _____________________________________________________________________________________________________________________

# General Validations and Configurations ______________________________________________________________________________
# cd indirection from /tools to the project source code, "." if no shift
set(PROJ_SRC_INDIR ..)  
add_compile_definitions(XHPTDC8_UTIL_EXPORTS)

# Get the platform and architecure ____________________________________________________________________________________
# Check supported architecture, and set `CRONO_GEN_ARCH` to `x86_64` for all
# variations of `x64` platforms, and to `x86` for all variations of `x86` 
# platforms.
# Set `CRONO_GEN_PLATFORM` to either `windows` or `linux`
SET(CRONO_GEN_PLATFORM "windows")
IF(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(CRONO_GEN_PLATFORM "linux")
ENDIF()

list(APPEND x64_archs Win64 AMD64 x86_64)
IF(CMAKE_SYSTEM_PROCESSOR IN_LIST x64_archs)
        set(CRONO_GEN_ARCH "x86_64")
ENDIF()

# Include directories paths ___________________________________________________________________________________________
include_directories(${CRONO_TARGET_NAME} PRIVATE    
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/../../include # On repository `./include`
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/src/ryml_src
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/src/ryml_src/c4/ext
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/src/ryml_src/c4/ext/fast_float/include/fast_float
)

# Link to driver library ______________________________________________________________________________________________
set(CRONO_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/../../lib)
set(CRONO_BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/${PROJ_SRC_INDIR}/../../bin)
link_directories(${CRONO_LIB_DIR})

# Add the target  _____________________________________________________________________________________________________
set(SOURCE 
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/base64.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/char_traits.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/error.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/format.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/language.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/memory_resource.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/memory_util.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/time.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/yml/common.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/yml/parse.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/yml/preprocess.cpp
        ${PROJ_SRC_INDIR}/src/ryml_src/c4/yml/tree.cpp
        ${PROJ_SRC_INDIR}/src/xhptdc8_util.cpp
        ${PROJ_SRC_INDIR}/src/xhptdc8_util_yaml.cpp
        ${PROJ_SRC_INDIR}/src/errors.h
)
set(HEADERS ${PROJ_SRC_INDIR}/src/xhptdc8_util_yaml.h)

add_library(${CRONO_TARGET_NAME} SHARED "${SOURCE}" "${HEADERS}")

target_compile_definitions(${CRONO_TARGET_NAME} PRIVATE 
    $<$<CONFIG:Debug>:CRONO_DEBUG_ENABLED XHPTDC8_VERBOSE_DEBUG>)

set_target_properties(${CRONO_TARGET_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CRONO_BIN_DIR} # for .dll, .so
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CRONO_BIN_DIR} # for .dlll, .so
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CRONO_LIB_DIR} # for .lib
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CRONO_LIB_DIR} # for .lib
)

IF ( CRONO_GEN_PLATFORM  STREQUAL "windows")
    # Windows-specific Configurations _________________________________________________________________________________
    target_link_libraries(${CRONO_TARGET_NAME} xhptdc8_driver_64)

ELSEIF (CRONO_GEN_PLATFORM STREQUAL "linux")   
    # Linux-specific Configurations ___________________________________________________________________________________
    add_compile_options(-fPIC -Wall $<$<CONFIG:Debug>:-g>)

    # Link to xhptdc8_driver library 
    target_link_libraries(${CRONO_TARGET_NAME} libxhptdc8_driver.a)
ENDIF()