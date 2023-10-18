cmake_minimum_required(VERSION 3.27.3)
project(delivery_FTL VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(class)
add_executable(delivery_FTL main.cpp)

target_link_libraries(main PUBLIC cls)