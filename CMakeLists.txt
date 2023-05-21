cmake_minimum_required(VERSION 3.20)
project(cosmicstreams)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)

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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/highjson>
        $<INSTALL_INTERFACE:include/highjson>
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/base>
        $<INSTALL_INTERFACE:include/base>
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/globals>
        $<INSTALL_INTERFACE:globals>
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/frame>
        $<INSTALL_INTERFACE:include/frame>
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/frame>
        $<INSTALL_INTERFACE:include/streamer>
)

target_link_libraries(
        FramePub
        PUBLIC
        Globals
        Pub
        highjson
)

###################################################################################
######### -- cosmicstreams -- this yields the final library libcosmicstreams.a ####
###################################################################################
add_library(
        cosmicstreams
)

target_sources(
        cosmicstreams
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/RecoStream.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/streamer>
        $<INSTALL_INTERFACE:src/RecoStream.cpp>
        $<INSTALL_INTERFACE:include/streamer>
)

target_include_directories(
        cosmicstreams
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/streamer>
        $<INSTALL_INTERFACE:include/streamer>
)

target_link_libraries(
        cosmicstreams
        PUBLIC
        FrameSub
        Globals
)

# set_target_properties(cosmicstreams PROPERTIES PUBLIC_HEADER "include/streamer/RecoStream.h")

#### This create the cosmicstreamsConfig.cmake file
set(cosmicstreams_VERSION 1.0.0)
include(GenerateExportHeader)
generate_export_header(cosmicstreams)
set_property(TARGET cosmicstreams PROPERTY VERSION ${cosmicstreams_VERSION})
set_property(TARGET cosmicstreams PROPERTY SOVERSION 1)
set_property(TARGET cosmicstreams PROPERTY INTERFACE_cosmicstreams_MAJOR_VERSION 1)
set_property(TARGET cosmicstreams APPEND PROPERTY COMPATIBLE_INTERFACE_STRING cosmicstreams_MAJOR_VERSION)

install(TARGETS cosmicstreams FrameSub Globals Sub highjson
        # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cosmicstreams
        EXPORT cosmicstreamsTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

install(FILES include/streamer/RecoStream.h "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreams_export.h"
        DESTINATION include
        COMPONENT Devel
        )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreams/cosmicstreamsConfigVersion.cmake"
        VERSION ${cosmicstreams_VERSION}
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT cosmicstreamsTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreams/cosmicstreamsTargets.cmake"
        NAMESPACE cosmicstreams::
        )

configure_file(cmake/cosmicstreamsConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreams/cosmicstreamsConfig.cmake"
        COPYONLY
        )

set(ConfigPackageLocation lib/cmake/cosmicstreams)
install(EXPORT cosmicstreamsTargets
        FILE
        cosmicstreamsTargets.cmake
        NAMESPACE
        cosmicstreams::
        DESTINATION
        ${ConfigPackageLocation}
        )
install(
        FILES
        cmake/cosmicstreamsConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreams/cosmicstreamsConfigVersion.cmake"
        DESTINATION
        ${ConfigPackageLocation}
        COMPONENT
        Devel
)


###################################################################################
###################################################################################
#### -> Add subdirectories
add_subdirectory(test)
