cmake_minimum_required(VERSION 3.10)
project(cosmicstreams)

add_subdirectory(test)

add_library(
    Pub
    src/Pub.cpp
)

target_include_directories(
        Pub
        PUBLIC
        include
)


find_package(cppzmq)

target_link_libraries(Pub cppzmq)
#target_link_libraries(sub cppzmq)

install(TARGETS Pub)
