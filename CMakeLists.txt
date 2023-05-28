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
        "${CMAKE_SOURCE_DIR}/include/highjson.h"
)

target_include_directories(
        highjson
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
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
    STATIC
    "${CMAKE_SOURCE_DIR}/src/Pub.cpp"
    "${CMAKE_SOURCE_DIR}/include/Pub.h"
)

target_include_directories(
        Pub
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
        Pub
        cppzmq
        highjson
        JsonCpp::JsonCpp
        Globals
)



############ -- Sub -- ############
add_library(
        Sub
        STATIC
        "${CMAKE_SOURCE_DIR}/src/Sub.cpp"
        "${CMAKE_SOURCE_DIR}/include/Sub.h"
)

target_include_directories(
        Sub
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
        Sub
        cppzmq
        highjson
)


########## -- Globals -- ##########
add_library(
        Globals
        "${CMAKE_SOURCE_DIR}/src/defaults.cpp"
        "${CMAKE_SOURCE_DIR}/include/defaults.h"
        "${CMAKE_SOURCE_DIR}/include/structs.h"
        "${CMAKE_SOURCE_DIR}/include/datatype_strings.h"
        "${CMAKE_SOURCE_DIR}/src/datatype_strings.cpp"
)

target_include_directories(
        Globals
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
        Globals
        PUBLIC
        JsonCpp::JsonCpp
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
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:src/RecoStream.cpp>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(
        cosmicstreams
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
        cosmicstreams
        PUBLIC
        Sub
        Pub
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

set(public_headers
    include/RecoStream.h
    include/Pub.h
    include/Sub.h
    include/highjson.h
    include/structs.h
    include/defaults.h
    )

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

message("Hello")
message("project_name: ${PROJECT_NAME}")
message("public_headers: ${public_headers}")
message("CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")

include(GNUInstallDirs)
install(TARGETS cosmicstreams Pub Globals Sub highjson
        # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cosmicstreams
        EXPORT cosmicstreamsTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        INCLUDES DESTINATION include/cosmicstreams
        )

#install(FILES include/RecoStream.h "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreams_export.h"
#        DESTINATION include
#        COMPONENT Devel
#        )

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
