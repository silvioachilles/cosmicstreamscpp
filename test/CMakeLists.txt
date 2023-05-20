
add_subdirectory(automated)
add_subdirectory(manual)


add_library(
        TestData
        "${CMAKE_SOURCE_DIR}/test/TestData.cpp"
        "${CMAKE_SOURCE_DIR}/test/TestData.h"
)

target_include_directories(
        TestData
        PUBLIC
        "${CMAKE_SOURCE_DIR}/test"
)

target_link_libraries(
        TestData
        PUBLIC
        Globals
        highjson
)


install(TARGETS TestData)
