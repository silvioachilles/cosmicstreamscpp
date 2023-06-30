cmake_minimum_required(VERSION 3.20)
# project(cosmicstreams)
project(cosmicstreamscpp)

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
        "${CMAKE_SOURCE_DIR}/include/cosmicstreamscpp/highjson.h"
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
    "${CMAKE_SOURCE_DIR}/include/cosmicstreamscpp/Pub.h"
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
        "${CMAKE_SOURCE_DIR}/include/cosmicstreamscpp/Sub.h"
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
        "${CMAKE_SOURCE_DIR}/include/cosmicstreamscpp/defaults.h"
        "${CMAKE_SOURCE_DIR}/include/cosmicstreamscpp/structs.h"
        "${CMAKE_SOURCE_DIR}/include/cosmicstreamscpp/datatype_strings.h"
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
######### The target that will be installed for external use ####
###################################################################################

add_library(cosmicstreamscpp STATIC)


target_sources(
        cosmicstreamscpp
        PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/datatype_strings.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/defaults.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/highjson.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/Pub.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/RecoStream.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/Sub.cpp>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:src/datatype_strings.cpp>
        $<INSTALL_INTERFACE:src/defaults.cpp>
        $<INSTALL_INTERFACE:src/highjson.cpp>
        $<INSTALL_INTERFACE:src/Pub.cpp>
        $<INSTALL_INTERFACE:src/RecoStream.cpp>
        $<INSTALL_INTERFACE:src/Sub.cpp>
        $<INSTALL_INTERFACE:include>
)

target_include_directories(
        cosmicstreamscpp
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(
        cosmicstreamscpp
        PUBLIC
        JsonCpp::JsonCpp
        cppzmq
)


# set_target_properties(cosmicstreams PROPERTIES PUBLIC_HEADER "include/streamer/RecoStream.h")
#### This create the cosmicstreamsConfig.cmake file
set(cosmicstreamscpp_VERSION 1.0.0)
include(GenerateExportHeader)
generate_export_header(cosmicstreamscpp)
set_property(TARGET cosmicstreamscpp PROPERTY VERSION ${cosmicstreamscpp_VERSION})
set_property(TARGET cosmicstreamscpp PROPERTY SOVERSION 1)
set_property(TARGET cosmicstreamscpp PROPERTY INTERFACE_cosmicstreamscpp_MAJOR_VERSION 1)
set_property(TARGET cosmicstreamscpp APPEND PROPERTY COMPATIBLE_INTERFACE_STRING cosmicstreams_MAJOR_VERSION)

set(public_headers
        include/cosmicstreamscpp/RecoStream.h
        # include/cosmicstreamscpp/Pub.h
        # include/cosmicstreamscpp/Sub.h
        # include/cosmicstreamscpp/highjson.h
        include/cosmicstreamscpp/structs.h
        # include/cosmicstreamscpp/defaults.h
        )

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")

message("Hello")
message("project_name: ${PROJECT_NAME}")
message("public_headers: ${public_headers}")
message("CMAKE_INSTALL_INCLUDEDIR: ${CMAKE_INSTALL_INCLUDEDIR}")

include(GNUInstallDirs)
install(TARGETS cosmicstreamscpp
        # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cosmicstreamscpp
        EXPORT cosmicstreamscppTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        # PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cosmicstreamscpp
        INCLUDES DESTINATION include/
        )

#install(FILES include/RecoStream.h "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreams_export.h"
#        DESTINATION include
#        COMPONENT Devel
#        )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreamscpp/cosmicstreamscppConfigVersion.cmake"
        VERSION ${cosmicstreamscpp_VERSION}
        COMPATIBILITY AnyNewerVersion
)

export(EXPORT cosmicstreamscppTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreamscpp/cosmicstreamscppTargets.cmake"
        NAMESPACE cosmicstreamscpp::
        )

configure_file(cmake/cosmicstreamscppConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreamscpp/cosmicstreamscppConfig.cmake"
        COPYONLY
        )

set(ConfigPackageLocation lib/cmake/cosmicstreamscpp)
install(EXPORT cosmicstreamscppTargets
        FILE
        cosmicstreamscppTargets.cmake
        NAMESPACE
        cosmicstreamscpp::
        DESTINATION
        ${ConfigPackageLocation}
        )
install(
        FILES
        cmake/cosmicstreamscppConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/cosmicstreamscpp/cosmicstreamscppConfigVersion.cmake"
        DESTINATION
        ${ConfigPackageLocation}
        COMPONENT
        Devel
)


###################################################################################
###################################################################################
#### -> Add subdirectories
add_subdirectory(test)
