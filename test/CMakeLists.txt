add_executable(test_point test_point.c)

target_link_libraries(test_point sxc cmocka)

add_test(Test_Point test_point)
