set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -fPIC -Wall -O0 -W -Wshadow -Wunused-variable \
                                                                   -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers \
                                                                   -Wno-deprecated -Woverloaded-virtual -Wwrite-strings")

set(SOURCES 
	src/position.cpp
	src/alivemonitor.cpp
	src/shape.cpp
	src/direction.cpp
	src/gametime.cpp
	src/entitylist.cpp
	src/fixeddirectionmover.cpp
	src/actor.cpp)

set(HEADERS 
	include/shape.h
	include/position.h
	include/direction.h
	include/vector.h
	include/movers/mover.h
	include/movers/fixeddirectionmover.h
	include/entity.h
	include/alivemonitor.h
	include/gametime.h
	include/entitylist.h
	include/actor.h)

add_library(engine ${SOURCES} ${HEADERS})

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
