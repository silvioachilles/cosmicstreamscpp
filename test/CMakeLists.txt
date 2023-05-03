
# test 01: test_Pub
add_executable(
        test_Pub
        "${CMAKE_SOURCE_DIR}/test/test_Pub.cpp"
)

target_link_libraries(
        test_Pub
        Pub
)

install(TARGETS test_Pub)

# test 02: test_Sub
add_executable(
        test_Sub
        "${CMAKE_SOURCE_DIR}/test/test_Sub.cpp"
)

target_link_libraries(
        test_Sub
        Sub
)

install(TARGETS test_Sub)

# test 03: test_StartSub
add_executable(
        test_StartSub
        "${CMAKE_SOURCE_DIR}/test/test_StartSub.cpp"
)

target_link_libraries(
        test_StartSub
        Start
)

install(TARGETS test_StartSub)
