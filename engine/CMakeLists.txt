set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fPIC -Wall -O0 -W -Wshadow -Wunused-variable \
                                                                   -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers \
                                                                   -Wno-deprecated -Woverloaded-virtual -Wwrite-strings")

set(SOURCES src/engine.cpp src/position.cpp src/shape.cpp include/position.h include/shape.h)

add_library(engine ${SOURCES})

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
