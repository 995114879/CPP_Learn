cmake_minimum_required(VERSION 3.10)
project(cmake_test VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(add)
add_subdirectory(sub)
add_subdirectory(test)

add_executable(cmake_test main.cpp)
target_link_libraries(cmake_test PRIVATE addlib sublib)

install(TARGETS cmake_test DESTINATION ${PROJECT_SOURCE_DIR}/bin)