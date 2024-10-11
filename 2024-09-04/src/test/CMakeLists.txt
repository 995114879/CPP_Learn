enable_testing()

add_executable(my_tests test.cpp)
target_link_libraries(my_tests addlib sublib)
add_test(NAME MyTests COMMAND my_tests)

