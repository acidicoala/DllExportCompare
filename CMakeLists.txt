cmake_minimum_required(VERSION 3.21)

include(KoalaBox/KoalaBox.cmake)

configure_globals(KoalaBox)

project(DllExportCompare)

configure_version_resource("Tool for comparing DLL exports")

configure_build_config()

add_executable(
    DllExportCompare

    src/main.cpp

    ${KOALABOX_SRC_DIR}/koalabox/koalabox.cpp
    ${KOALABOX_SRC_DIR}/koalabox/loader/loader.cpp
    ${KOALABOX_SRC_DIR}/koalabox/util/util.cpp
    ${KOALABOX_SRC_DIR}/koalabox/win_util/win_util.cpp
)

configure_precompile_headers(${CMAKE_PROJECT_NAME} ${SRC_DIR}/pch.hpp)


configure_include_directories()

configure_dependencies(${CMAKE_PROJECT_NAME} spdlog)
