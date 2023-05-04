cmake_minimum_required(VERSION 3.20)
project(cosmicstreams)

find_package(cppzmq)
find_package(jsoncpp CONFIG REQUIRED)

# Pub and Sub are low-level targets.
############ -- Pub -- ############
add_library(
    Pub
    "${CMAKE_SOURCE_DIR}/src/Pub.cpp"
    "${CMAKE_SOURCE_DIR}/include/base/Pub.h"
)

target_include_directories(
        Pub
        PRIVATE
        "${CMAKE_SOURCE_DIR}/include/base"
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
        "${CMAKE_SOURCE_DIR}/include/base/Sub.h"
)

target_include_directories(
        Sub
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/base"
)

target_link_libraries(
        Sub
        cppzmq
)

install(TARGETS Sub)

########## -- Globals -- ##########
add_library(
        Globals
        "${CMAKE_SOURCE_DIR}/globals/defaults.cpp"
        "${CMAKE_SOURCE_DIR}/globals/defaults.h"
)

target_include_directories(
        Globals
        PUBLIC
        "${CMAKE_SOURCE_DIR}/globals"
)

install(TARGETS Globals)


########### -- start -- ###########
add_library(
        Start
        "${CMAKE_SOURCE_DIR}/src/StartSub.cpp"
        "${CMAKE_SOURCE_DIR}/include/start/StartSub.h"
        "${CMAKE_SOURCE_DIR}/src/StartPub.cpp"
        "${CMAKE_SOURCE_DIR}/include/start/StartPub.h"
)

target_include_directories(
        Start
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/start"
)

target_link_libraries(
        Start
        PUBLIC
        Globals
        Sub
        Pub
        JsonCpp::JsonCpp
)

install(TARGETS Start)

########### -- frame -- ###########
add_library(
        Frame
        "${CMAKE_SOURCE_DIR}/src/FrameSub.cpp"
        "${CMAKE_SOURCE_DIR}/include/frame/FrameSub.h"
)

target_include_directories(
        Frame
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/frame"
)

target_link_libraries(
        Frame
        PUBLIC
        Globals
        Sub
        Pub
        JsonCpp::JsonCpp
)

install(TARGETS Frame)


#### -> Add subdirectories
add_subdirectory(test)
