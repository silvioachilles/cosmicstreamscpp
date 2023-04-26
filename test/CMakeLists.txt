

add_executable(
        test_Pub
        test_Pub.cpp
)

target_link_libraries(
        test_Pub
        Pub
)

#target_include_directories(
#        test_Pub
#        PUBLIC
#        ../include
#)

install(TARGETS test_Pub)
