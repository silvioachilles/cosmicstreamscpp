cmake_minimum_required(VERSION 3.20)
project(cosmicstreams)

find_package(cppzmq)
find_package(jsoncpp CONFIG REQUIRED)

# Pub and Sub are low-level targets.
############ -- Pub -- ############
add_library(
    Pub
    "${CMAKE_SOURCE_DIR}/src/Pub.cpp"
    "${CMAKE_SOURCE_DIR}/include/Base/Pub.h"
)

target_include_directories(
        Pub
        PRIVATE
        "${CMAKE_SOURCE_DIR}/include/Base"
)

target_link_libraries(
        Pub
        cppzmq
)

install(TARGETS Pub)


############ -- Sub -- ############
add_library(
        Sub
        STATIC
        "${CMAKE_SOURCE_DIR}/src/Sub.cpp"
        "${CMAKE_SOURCE_DIR}/include/Base/Sub.h"
)

target_include_directories(
        Sub
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/Base"
)

target_link_libraries(
        Sub
        cppzmq
)

install(TARGETS Sub)

########## -- Globals -- ##########
add_library(
        Globals
        "${CMAKE_SOURCE_DIR}/src/defaults.cpp"
        "${CMAKE_SOURCE_DIR}/include/Globals/defaults.h"
)

target_include_directories(
        Globals
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/Globals"
)

install(TARGETS Globals)


########### -- Start -- ###########
add_library(
        Start
        "${CMAKE_SOURCE_DIR}/src/StartSub.cpp"
        "${CMAKE_SOURCE_DIR}/include/Start/StartSub.h"
)

target_include_directories(
        Start
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/Start"
)

target_link_libraries(
        Start
        Globals
        Sub
        JsonCpp::JsonCpp
)

install(TARGETS Start)

add_subdirectory(test)