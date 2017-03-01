cmake_minimum_required(VERSION 2.8)

project(Masteroids CXX)

set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/engine/include)
add_subdirectory(engine)
add_subdirectory(game)

add_dependencies(masteroids engine)
