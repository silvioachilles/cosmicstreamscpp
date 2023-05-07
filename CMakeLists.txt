cmake_minimum_required(VERSION 3.20)
project(cosmicstreams)

find_package(cppzmq)
find_package(jsoncpp CONFIG REQUIRED)

# highjson is a target that brings the jsoncpp to a higher level so that
# jsoncpp can be used with single function calls.
############ -- highjson -- ############
add_library(
        highjson
        "${CMAKE_SOURCE_DIR}/src/highjson.cpp"
        "${CMAKE_SOURCE_DIR}/include/highjson/highjson.h"
)

target_include_directories(
        highjson
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/highjson"
)

target_link_libraries(
        highjson
        PUBLIC
        JsonCpp::JsonCpp
)

install(TARGETS highjson)

# Pub and Sub are low-level targets.
############ -- Pub -- ############
add_library(
    Pub
    "${CMAKE_SOURCE_DIR}/src/Pub.cpp"
    "${CMAKE_SOURCE_DIR}/include/base/Pub.h"
)

target_include_directories(
        Pub
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/base"
)

target_link_libraries(
        Pub
        cppzmq
        highjson
        JsonCpp::JsonCpp
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
        highjson
)

install(TARGETS Sub)

########## -- Globals -- ##########
add_library(
        Globals
        "${CMAKE_SOURCE_DIR}/globals/defaults.cpp"
        "${CMAKE_SOURCE_DIR}/globals/defaults.h"
        "${CMAKE_SOURCE_DIR}/globals/structs.h"
)

target_include_directories(
        Globals
        PUBLIC
        "${CMAKE_SOURCE_DIR}/globals"
)

target_link_libraries(
        Globals
        PUBLIC
        JsonCpp::JsonCpp
)

install(TARGETS Globals)

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
        highjson
)

install(TARGETS Frame)

######### -- RecoStream -- #########
add_library(
        RecoStream
        "${CMAKE_SOURCE_DIR}/src/RecoStream.cpp"
        "${CMAKE_SOURCE_DIR}/include/streamer/RecoStream.h"
)

target_include_directories(
        RecoStream
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/streamer"
)

target_link_libraries(
        RecoStream
        PUBLIC
        Sub
        Frame
)

install(TARGETS RecoStream)

#### -> Add subdirectories
add_subdirectory(test)
