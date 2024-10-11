cmake_minimum_required(VERSION 3.10)

project(get_client)

find_package(CURL REQUIRED)

add_executable(get_client get_client.cpp)
target_link_libraries(get_client CURL::libcurl)
include_directories(${CURL_INCLUDE_DIRS})