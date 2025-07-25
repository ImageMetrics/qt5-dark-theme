cmake_minimum_required(VERSION 3.16)

project(Kvantum)

set(CMAKE_CXX_STANDARD 17)

# Find Qt from Conan - this provides Qt5::Core, Qt5::Widgets, Qt5::Svg, etc.
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Svg Gui)

message(STATUS "Qt5 found via Conan")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Using GLOB_RECURSE with CONFIGURE_DEPENDS (CMake 3.12+)
# This tells CMake to check for file changes at build time
file(GLOB_RECURSE KVANTUM_SOURCES CONFIGURE_DEPENDS 
    src/*.cpp
)
file(GLOB_RECURSE KVANTUM_HEADERS CONFIGURE_DEPENDS 
    src/*.h 
    include/*.h
)
file(GLOB KVANTUM_THEMES CONFIGURE_DEPENDS 
    bin/themes/kvantum/*/*.qrc
)

add_library(Kvantum STATIC
    ${KVANTUM_SOURCES}
    ${KVANTUM_HEADERS}
    ${KVANTUM_THEMES}
    default/defaulttheme.qrc)

target_link_libraries(Kvantum Qt5::Widgets Qt5::Core Qt5::Svg)
target_include_directories(Kvantum PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")
target_include_directories(Kvantum PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include")
target_compile_definitions(Kvantum PRIVATE DATADIR)

add_executable(Test
    ThemeTest/main.cpp
    ThemeTest/mainwindow.cpp
    ThemeTest/mainwindow.h
    ThemeTest/mainwindow.ui
    ThemeTest/ThemeTest.qrc)
target_link_libraries(Test Qt5::Widgets Qt5::Core)
target_include_directories(Test PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include")

# No installation needed - Conan handles packaging directly

message("-- Qt version ${Qt5Core_VERSION_STRING} found via Conan")