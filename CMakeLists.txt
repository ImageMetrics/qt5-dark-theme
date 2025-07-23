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

add_library(Kvantum STATIC
    src/eventFiltering.cpp
    src/polishing.cpp
    src/animation.cpp
    src/animation.h
    src/blurhelper.cpp
    src/blurhelper.h
    src/kcolorspaces.cpp
    src/kcolorspaces_p.h
    src/kcolorutils.h
    src/kcolorutils.cpp
    src/kguiaddons_colorhelpers_p.h
    src/kguiaddons_export.h
    src/Kvantum.cpp
    src/Kvantum.h
    src/pbscolorconfig.h
    src/pbscolorconfig.cpp
    src/pbscolorscheme.cpp
    src/pbscolorscheme.h
    src/shortcuthandler.cpp
    src/shortcuthandler.h
    src/specs.h
    src/ThemeConfig.h
    src/ThemeConfig.cpp
    src/windowmanager.cpp
    src/windowmanager.h
    src/x11wmmove.cpp
    src/x11wmmove.h
    src/plugin.h
    src/plugin.cpp
    default/defaulttheme.qrc
    bin/themes/kvantum/DarkLines/DarkLines.qrc
    bin/themes/kvantum/KvCurves/KvCurves.qrc
    bin/themes/kvantum/KvDarkRed/KvDarkRed.qrc
    bin/themes/kvantum/kvGlowDark/kvGlowDark.qrc)

target_link_libraries(Kvantum Qt5::Widgets Qt5::Core Qt5::Svg)
target_include_directories(Kvantum PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")
target_compile_definitions(Kvantum PRIVATE DATADIR)

add_executable(Test
    ThemeTest/main.cpp
    ThemeTest/mainwindow.cpp
    ThemeTest/mainwindow.h
    ThemeTest/mainwindow.ui
    ThemeTest/ThemeTest.qrc)
target_link_libraries(Test Qt5::Widgets Qt5::Core)
target_include_directories(Test PRIVATE "${CMAKE_CURRENT_LIST_DIR}/src")

# Install build targets
install(TARGETS Kvantum DESTINATION lib)
install(TARGETS Test DESTINATION bin)

# Install headers
install(DIRECTORY src/ DESTINATION include/kvantum
    FILES_MATCHING PATTERN "*.h"
    PATTERN "*_p.h" EXCLUDE)

# Install theme files
install(DIRECTORY default/ DESTINATION share/kvantum/themes/default)
install(DIRECTORY bin/themes/ DESTINATION share/kvantum/themes)

message("-- Qt version ${Qt5Core_VERSION_STRING} found via Conan")