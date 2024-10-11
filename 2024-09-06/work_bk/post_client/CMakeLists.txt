cmake_minimum_required(VERSION 3.10)

project(post_client)

find_package(CURL REQUIRED)

add_executable(post_client post_client.cpp)
target_link_libraries(post_client CURL::libcurl)
include_directories(${CURL_INCLUDE_DIRS})
