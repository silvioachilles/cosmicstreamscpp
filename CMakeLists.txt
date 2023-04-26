cmake_minimum_required(VERSION 3.10)
project(cosmicstreams)

add_subdirectory(test)

find_package(cppzmq)

# Pub and Sub are low-level targets.
############ -- Pub -- ############
add_library(
    Pub
    src/Pub.cpp
)

target_include_directories(
        Pub
        PUBLIC
        include
)

target_link_libraries(Pub cppzmq)


############ -- Sub -- ############
add_library(
        Sub
        src/Sub.cpp
)

target_include_directories(
        Sub
        PUBLIC
        include
)

target_link_libraries(Sub cppzmq)


########### -- Start -- ###########
add_library(
        Start
        src/Start.cpp
)

target_include_directories(
        Start
        PUBLIC
        include
)

target_link_libraries(
        Start
        PUBLIC
        Sub
        Pub
        cppzmq
)

install(TARGETS Pub Sub Start)
