include(CTest)

# test 00: test_highjson
add_executable(
        ctest_highjson
        "${CMAKE_SOURCE_DIR}/test/automated/test_highjson.cpp"
)

target_link_libraries(
        ctest_highjson
        highjson
)

enable_testing()
add_test(NAME ctest_highjson COMMAND $<TARGET_FILE:ctest_highjson>)

# test 01: test_Pub
add_executable(
        ctest_Pub
        "${CMAKE_SOURCE_DIR}/test/automated/test_Pub.cpp"
)

target_link_libraries(
        ctest_Pub
        Pub
)

add_test(NAME ctest_Pub COMMAND $<TARGET_FILE:ctest_Pub>)

# test 02: test_sub
add_executable(
        ctest_Sub
        "${CMAKE_SOURCE_DIR}/test/automated/test_Sub.cpp"
)

target_link_libraries(
        ctest_Sub
        Sub
)

add_test(NAME ctest_Sub COMMAND $<TARGET_FILE:ctest_Sub>)

# test 03: test_PubSub
add_executable(
        ctest_PubSub
        "${CMAKE_SOURCE_DIR}/test/automated/test_PubSub.cpp"
)

target_link_libraries(
        ctest_PubSub
        Pub
        Sub
)

add_test(NAME ctest_PubSub COMMAND $<TARGET_FILE:ctest_PubSub>)

# test 05: test_FramePub
add_executable(
        ctest_FramePub
        "${CMAKE_SOURCE_DIR}/test/automated/test_FramePub.cpp"
)

target_link_libraries(
        ctest_FramePub
        Pub
)

add_test(NAME ctest_FramePub COMMAND $<TARGET_FILE:ctest_FramePub>)

# test 06: test_FrameSub
add_executable(
        ctest_FrameSub
        "${CMAKE_SOURCE_DIR}/test/automated/test_FrameSub.cpp"
)

target_link_libraries(
        ctest_FrameSub
        Sub
)

add_test(NAME ctest_FrameSub COMMAND $<TARGET_FILE:ctest_FrameSub>)

# test 06: test_FramePubFrameSub
add_executable(
        ctest_FramePubFrameSub
        "${CMAKE_SOURCE_DIR}/test/automated/test_FramePubFrameSub.cpp"
)

target_link_libraries(
        ctest_FramePubFrameSub
        Pub
        Sub
        TestData
)

add_test(NAME ctest_FramePubFrameSub COMMAND $<TARGET_FILE:ctest_FramePubFrameSub>)


# test 07: test_RecoStream
add_executable(
        ctest_RecoStream
        "${CMAKE_SOURCE_DIR}/test/automated/test_RecoStream.cpp"
)

target_link_libraries(
        ctest_RecoStream
        cosmicstreamscpp
        Pub
        Sub
        Globals
        TestData
)

add_test(NAME ctest_RecoStream COMMAND $<TARGET_FILE:ctest_RecoStream>)
