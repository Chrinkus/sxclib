add_executable(test_point 	test_point.c)
add_executable(test_dyn_queue	test_dynamic_queue.c)

target_link_libraries(test_point	sxc cmocka)
target_link_libraries(test_dyn_queue	sxc cmocka)

add_test(Test_Point	test_point)
add_test(Test_dyn_queue	test_dyn_queue)
