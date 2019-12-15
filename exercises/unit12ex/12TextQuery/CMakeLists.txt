cmake_minimum_required(VERSION 3.0)

project(Text_Query)

add_subdirectory(class)

include_directories(./class)

add_executable(${PROJECT_NAME} demo.cpp)

target_link_libraries(${PROJECT_NAME} class)