cmake_minimum_required(VERSION 3.20)
project(PipsiHSR LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(GLOBAL_DIR "${CMAKE_SOURCE_DIR}/include/global")
set(DETOURS_LIB "${CMAKE_SOURCE_DIR}/libs/detours.lib")

if(NOT EXISTS "${GLOBAL_DIR}/.git")
    message(STATUS "Cloning AnimeSDK submodule into include/global...")
    execute_process(
        COMMAND git submodule update --init --recursive
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${SRC_DIR}/*.cpp"
)

if(NOT SRC_FILES)
    message(FATAL_ERROR "No source files found in ${SRC_DIR}!")
else()
    message(STATUS "Found ${SRC_FILES}")
endif()

add_library(PipsiHSR SHARED ${SRC_FILES})

target_include_directories(PipsiHSR PRIVATE
    "${SRC_DIR}"
    "${CMAKE_SOURCE_DIR}/include"
    "${GLOBAL_DIR}"
    "${SRC_DIR}/Common"
)

target_compile_definitions(PipsiHSR PRIVATE
    UNICODE
    _UNICODE
    $<$<CONFIG:Debug>:_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
    _CONSOLE
)

target_compile_options(PipsiHSR PRIVATE /W3 /permissive-)

if(EXISTS "${SRC_DIR}/pch.h")
    target_precompile_headers(PipsiHSR PRIVATE "${SRC_DIR}/pch.h")
endif()

target_link_libraries(PipsiHSR PRIVATE
    d3d11
    dxgi
    dxguid
    "${DETOURS_LIB}"
)

set_target_properties(PipsiHSR PROPERTIES
    OUTPUT_NAME "cheat.dll"
)
