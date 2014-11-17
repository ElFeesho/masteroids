cmake_minimum_required(VERSION 2.8.4)
project(masteroids)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(SDL REQUIRED)

set(SOURCE_FILES
    gfx/gfx.h
    gfx/sdlgfx.cpp
    images/asteroid_banner.h
    images/controllers.h
    images/controls_img.h
    images/game_over_img.h
    images/options_img.h
    input/gamepad.h
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
    libwiiwrap/ogcsys.h
    movers/bulletmover.h
    movers/fixeddirectionmover.cpp
    movers/fixeddirectionmover.h
    movers/shipmover.h
    renderers/aboutrenderer.h
    renderers/asteroidrenderer.h
    renderers/bulletrenderer.h
    renderers/debrisrender.h
    renderers/menurenderer.h
    renderers/optionsrenderer.cpp
    renderers/optionsrenderer.h
    renderers/shiprenderer.cpp
    renderers/shiprenderer.h
    about.cpp
    about.h
    images/about_img.h
    alivemonitor.cpp
    alivemonitor.h
    asteroid.cpp
    asteroid.h
    bullet.cpp
    bullet.h
    controlconf.cpp
    controlconf.h
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
    gamescreen.cpp
    gamescreen.h
    gameoverscreen.cpp
    gameoverscreen.h
    renderers/gameoverrenderer.cpp
    renderers/gameoverrenderer.h
    renderers/ingamemenurenderer.cpp
    renderers/ingamemenurenderer.h
    renderers/livesrenderer.cpp
    renderers/livesrenderer.h
    ingame.cpp
    ingame.h
    main.cpp
    menu.cpp
    menu.h
    menuscreen.cpp
    menuscreen.h
    movers/mover.h
    options.cpp
    options.h
    position.cpp
    position.h
    renderers/renderer.h
    screen.h
    screenmanager.cpp
    screenmanager.h
    shape.cpp
    shape.h
    ship.cpp
    ship.h
    gametime.cpp
    gametime.h
    vector.h)

add_executable(masteroids ${SOURCE_FILES})

include_directories(${SDL_INCLUDE_DIR})
include_directories("libwiiwrap")
include_directories(".")

set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa")

target_link_libraries(masteroids -lSDLmain -lSDL -lSDL_gfx -lm)
