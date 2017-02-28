cmake_minimum_required(VERSION 2.8.4)
project(masteroids)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fPIC -Wall -O0 -W -Wshadow -Wunused-variable \
                                                                   -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers \
                                                                   -Wno-deprecated -Woverloaded-virtual -Wwrite-strings")

#SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")


set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

set(SOURCE_FILES
    menu/menuscreenitem.h
    gfx/gfx.h
    images/asteroid_banner.h
    bulletfactory.h
    bulletgenerator.cpp
    bulletgenerator.h
    images/controllers.h
    images/controls_img.h
    images/game_over_img.h
    images/options_img.h
    input/gamepad.h
    input/gamepad.cpp
    directioncontroller.h
    input/gamepadinputmanager.cpp
    input/gamepadinputmanager.h
    input/keyboardsource.cpp
    input/keyboardsource.h
    libwiiwrap/ogc/lwp_watchdog.cpp
    libwiiwrap/ogc/lwp_watchdog.h
    libwiiwrap/wiiuse/wpad.cpp
    libwiiwrap/wiiuse/wpad.h
    libwiiwrap/gccore.cpp
    libwiiwrap/gccore.h
    libwiiwrap/ogcsys.cpp
    shipfactory.h
    directioncontroller.h
    libwiiwrap/ogcsys.h
    movers/bulletmover.h
    movers/fixeddirectionmover.cpp
    movers/fixeddirectionmover.h
    movers/shipmover.h
    movers/shipmover.cpp
    renderers/aboutrenderer.h
    renderers/asteroidrenderer.h
    renderers/asteroidrenderer.cpp
    renderers/bulletrenderer.h
    renderers/bulletrenderer.cpp
    renderers/debrisrender.h
    renderers/menurenderer.h
    renderers/optionsrenderer.cpp
    renderers/optionsrenderer.h
    renderers/shiprenderer.cpp
    renderers/shiprenderer.h
    menu/about.cpp
    menu/about.h
    playermanager.cpp
    playermanager.h
    images/about_img.h
    actor.cpp
    actor.h
    asteroidfactory.h
    alivemonitor.cpp
    movers/bulletmover.cpp
    alivemonitor.h
    menu/controlconf.cpp
    menu/controlconf.h
    debris.cpp
    debris.h
    debrisfountain.cpp
    debrisfountain.h
    direction.cpp
    direction.h
    elapsedtimetolive.cpp
    elapsedtimetolive.h
    entity.h
    entitylist.cpp
    entitylist.h
    font5.h
    gameover.cpp
    gameover.h
    screens/gamescreen.cpp
    screens/gamescreen.h
    screens/gameoverscreen.cpp
    screens/gameoverscreen.h
    renderers/gameoverrenderer.cpp
    renderers/gameoverrenderer.h
    renderers/pausedialogrenderer.cpp
    renderers/pausedialogrenderer.h
    renderers/livesrenderer.cpp
    renderers/livesrenderer.h
    renderers/scorerenderer.cpp
    renderers/scorerenderer.h
    pausedialog.cpp
    pausedialog.h
    main.cpp
    menu/menu.cpp
    menu/menu.h
    screens/menuscreen.cpp
    screens/menuscreen.h
    movers/mover.h
    menu/options.cpp
    menu/options.h
    position.cpp
    position.h
    renderers/renderer.h
    screens/screen.h
    screenmanager.cpp
    screenmanager.h
    shape.cpp
    shape.h
    gametime.cpp
    gametime.h
    gfx/sfmlgfx.cpp
    gfx/sfmlgfx.h
    asteroidfactory.cpp
    vector.h)

include_directories("libwiiwrap")
include_directories(".")


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa")
   add_executable(masteroids MACOSX_BUNDLE ${SOURCE_FILES} resources.mm boldfont.ttf regularfont.ttf)
   add_definitions("-DMACOSX")
   SET_SOURCE_FILES_PROPERTIES(
    boldfont.ttf
    regularfont.ttf
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources)
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(masteroids ${SOURCE_FILES})
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

include_directories(${SFML_INCLUDE_DIR})

target_link_libraries(masteroids -lm ${SFML_LIBRARIES})
