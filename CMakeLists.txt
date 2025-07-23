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
    bin/themes/kvantum/Adapta/Adapta.qrc
    bin/themes/kvantum/AdaptaNokto/AdaptaNokto.qrc
    bin/themes/kvantum/Blossom/Blossom.qrc
    bin/themes/kvantum/Charcoal/Charcoal.qrc
    bin/themes/kvantum/DarkLines/DarkLines.qrc
    bin/themes/kvantum/KvAdapta/KvAdapta.qrc
    bin/themes/kvantum/KvAdaptaDark/KvAdaptaDark.qrc
    bin/themes/kvantum/KvAmbiance/KvAmbiance.qrc
    bin/themes/kvantum/KvAmbience/KvAmbience.qrc
    bin/themes/kvantum/KvArc/KvArc.qrc
    bin/themes/kvantum/KvArcDark/KvArcDark.qrc
    bin/themes/kvantum/KvArcDarker/KvArcDarker.qrc
    bin/themes/kvantum/KvBaghiraAqua/KvBaghiraAqua.qrc
    bin/themes/kvantum/KvBaghiraAquaMetal/KvBaghiraAquaMetal.qrc
    bin/themes/kvantum/KvBeige/KvBeige.qrc
    bin/themes/kvantum/KvCupertino/KvCupertino.qrc
    bin/themes/kvantum/KvCurves/KvCurves.qrc
    bin/themes/kvantum/KvCurves3d/KvCurves3d.qrc
    bin/themes/kvantum/KvCurvesLight/KvCurvesLight.qrc
    bin/themes/kvantum/KvCyan/KvCyan.qrc
    bin/themes/kvantum/KvDark/KvDark.qrc
    bin/themes/kvantum/KvDarkRed/KvDarkRed.qrc
    bin/themes/kvantum/KvDynamo/KvDynamo.qrc
    bin/themes/kvantum/KvFlat/KvFlat.qrc
    bin/themes/kvantum/KvFlatLight/KvFlatLight.qrc
    bin/themes/kvantum/KvFlatRed/KvFlatRed.qrc
    bin/themes/kvantum/KvGlass/KvGlass.qrc
    bin/themes/kvantum/KvGlow/KvGlow.qrc
    bin/themes/kvantum/KvGlowDark/KvGlowDark.qrc
    bin/themes/kvantum/KvGnome/KvGnome.qrc
    bin/themes/kvantum/KvGnomeAlt/KvGnomeAlt.qrc
    bin/themes/kvantum/KvGnomeDark/KvGnomeDark.qrc
    bin/themes/kvantum/KvGnomish/KvGnomish.qrc
    bin/themes/kvantum/KvGray/KvGray.qrc
    bin/themes/kvantum/KvHybrid/KvHybrid.qrc
    bin/themes/kvantum/KvOxygen/KvOxygen.qrc
    bin/themes/kvantum/KvRoughGlass/KvRoughGlass.qrc
    bin/themes/kvantum/KvSilver/KvSilver.qrc
    bin/themes/kvantum/KvSimplicity/KvSimplicity.qrc
    bin/themes/kvantum/KvSimplicityDark/KvSimplicityDark.qrc
    bin/themes/kvantum/KvSimplicityTurquoise/KvSimplicityTurquoise.qrc
    bin/themes/kvantum/KvStriped/KvStriped.qrc
    bin/themes/kvantum/KvantumAlt/KvantumAlt.qrc
    bin/themes/kvantum/KvantumLyoko/KvantumLyoko.qrc
    bin/themes/kvantum/Materia/Materia.qrc
    bin/themes/kvantum/MateriaDark/MateriaDark.qrc
    bin/themes/kvantum/MateriaLight/MateriaLight.qrc
    bin/themes/kvantum/Retrosmart/Retrosmart.qrc)

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