
# test 01: test_Pub
add_executable(
        test_Pub
        test_Pub.cpp
)

target_link_libraries(
        test_Pub
        Pub
)

# test 02: test_Sub
add_executable(
        test_Sub
        test_Sub.cpp
)

target_link_libraries(
        test_Sub
        Sub
)

install(TARGETS test_Pub test_Sub)
