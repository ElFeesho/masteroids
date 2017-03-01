set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fPIC -Wall -O0 -W -Wshadow -Wunused-variable \
                                                                   -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers \
                                                                   -Wno-deprecated -Woverloaded-virtual -Wwrite-strings")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)

set(SOURCE_FILES
    src/menu/menuscreenitem.h
    src/images/asteroid_banner.h
    src/bulletfactory.h
    src/images/controllers.h
    src/images/controls_img.h
    src/images/game_over_img.h
    src/images/options_img.h
    src/input/gamepad.h
    src/input/gamepad.cpp
    src/directioncontroller.h
    src/input/gamepadinputmanager.cpp
    src/input/gamepadinputmanager.h
    src/input/keyboardsource.cpp
    src/input/keyboardsource.h
    src/shipfactory.h
    src/directioncontroller.h
    src/movers/shipmover.h
    src/movers/shipmover.cpp
    src/renderers/aboutrenderer.h
    src/renderers/asteroidrenderer.h
    src/renderers/asteroidrenderer.cpp
    src/renderers/bulletrenderer.h
    src/renderers/bulletrenderer.cpp
    src/renderers/debrisrender.h
    src/renderers/menurenderer.h
    src/renderers/optionsrenderer.cpp
    src/renderers/optionsrenderer.h
    src/renderers/shiprenderer.cpp
    src/renderers/shiprenderer.h
    src/menu/about.cpp
    src/menu/about.h
    src/playermanager.cpp
    src/playermanager.h
    src/images/about_img.h
    src/asteroidfactory.h
    src/menu/controlconf.cpp
    src/menu/controlconf.h
    src/debrisfountain.cpp
    src/debrisfountain.h
    src/elapsedtimetolive.cpp
    src/elapsedtimetolive.h
    src/font5.h
    src/gameover.cpp
    src/gameover.h
    src/screens/gamescreen.cpp
    src/screens/gamescreen.h
    src/screens/gameoverscreen.cpp
    src/screens/gameoverscreen.h
    src/renderers/gameoverrenderer.cpp
    src/renderers/gameoverrenderer.h
    src/renderers/pausedialogrenderer.cpp
    src/renderers/pausedialogrenderer.h
    src/renderers/livesrenderer.cpp
    src/renderers/livesrenderer.h
    src/renderers/scorerenderer.cpp
    src/renderers/scorerenderer.h
    src/pausedialog.cpp
    src/pausedialog.h
    src/main.cpp
    src/menu/menu.cpp
    src/menu/menu.h
    src/screens/menuscreen.cpp
    src/screens/menuscreen.h
    src/menu/options.cpp
    src/menu/options.h
    src/screens/screen.h
    src/screenmanager.cpp
    src/screenmanager.h
    src/gfx/sfmlgfx.cpp
    src/gfx/sfmlgfx.h
    src/asteroidfactory.cpp)

include_directories("src/")


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
   set(CMAKE_EXE_LINKER_FLAGS "-framework Cocoa")
   add_executable(masteroids MACOSX_BUNDLE ${SOURCE_FILES} src/resources.mm resources/boldfont.ttf resources/regularfont.ttf)
   add_definitions("-DMACOSX")
   SET_SOURCE_FILES_PROPERTIES(
    resources/boldfont.ttf
    resources/regularfont.ttf
    PROPERTIES
    MACOSX_PACKAGE_LOCATION Resources)
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_executable(masteroids ${SOURCE_FILES})
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

include_directories(${SFML_INCLUDE_DIR})
target_include_directories(masteroids PRIVATE ${ENGINE_INCLUDE_DIR})
target_link_libraries(masteroids m engine ${SFML_LIBRARIES} ${ENGINE})

