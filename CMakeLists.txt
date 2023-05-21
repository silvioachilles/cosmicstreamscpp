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


########## -- Globals -- ##########
add_library(
        Globals
        "${CMAKE_SOURCE_DIR}/globals/defaults.cpp"
        "${CMAKE_SOURCE_DIR}/globals/defaults.h"
        "${CMAKE_SOURCE_DIR}/globals/structs.h"
        "${CMAKE_SOURCE_DIR}/globals/datatype_strings.h"
        "${CMAKE_SOURCE_DIR}/globals/datatype_strings.cpp"
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


########### -- FrameSub -- ###########
add_library(
        FrameSub
        "${CMAKE_SOURCE_DIR}/src/FrameSub.cpp"
        "${CMAKE_SOURCE_DIR}/include/frame/FrameSub.h"
)

target_include_directories(
        FrameSub
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/frame"
)

target_link_libraries(
        FrameSub
        PUBLIC
        Globals
        Sub
        highjson
)


########### -- FramePub -- ###########
add_library(
        FramePub
        "${CMAKE_SOURCE_DIR}/src/FramePub.cpp"
        "${CMAKE_SOURCE_DIR}/include/frame/FramePub.h"
)

target_include_directories(
        FramePub
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/frame"
)

target_link_libraries(
        FramePub
        PUBLIC
        Globals
        Pub
        highjson
)


######### -- RecoStream -- #########
add_library(
        cosmicstreams
        "${CMAKE_SOURCE_DIR}/src/RecoStream.cpp"
        "${CMAKE_SOURCE_DIR}/include/streamer/RecoStream.h"
)

target_include_directories(
        cosmicstreams
        PUBLIC
        "${CMAKE_SOURCE_DIR}/include/streamer"
)

target_link_libraries(
        cosmicstreams
        PUBLIC
        FrameSub
        Globals
)

install(TARGETS cosmicstreams)

#### -> Add subdirectories
add_subdirectory(test)
