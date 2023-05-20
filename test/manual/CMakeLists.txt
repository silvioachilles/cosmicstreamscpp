# test 01: test_Pub
add_executable(
        test_Pub
        "${CMAKE_SOURCE_DIR}/test/manual/test_Pub.cpp"
)

target_link_libraries(
        test_Pub
        Pub
)

install(TARGETS test_Pub)

# test 02: test_Sub
add_executable(
        test_Sub
        "${CMAKE_SOURCE_DIR}/test/manual/test_Sub.cpp"
)

target_link_libraries(
        test_Sub
        Sub
)

install(TARGETS test_Sub)

# test 03: test_Sub_start
add_executable(
        test_Sub_start
        "${CMAKE_SOURCE_DIR}/test/manual/test_Sub_start.cpp"
)

target_link_libraries(
        test_Sub_start
        Sub
)

install(TARGETS test_Sub_start)

# test 04: test_Pub_start
add_executable(
        test_Pub_start
        "${CMAKE_SOURCE_DIR}/test/manual/test_Pub_start.cpp"
)

target_link_libraries(
        test_Pub_start
        PUBLIC
        Pub
        TestData
)

install(TARGETS test_Pub_start)

# test 05: test_FrameSub
add_executable(
        test_FrameSub
        "${CMAKE_SOURCE_DIR}/test/manual/test_FrameSub.cpp"
)

target_link_libraries(
        test_FrameSub
        FrameSub
)



# test 06: test_RecoStream
add_executable(
        test_RecoStream
        "${CMAKE_SOURCE_DIR}/test/manual/test_RecoStream.cpp"
)

target_link_libraries(
        test_RecoStream
        RecoStream
)
