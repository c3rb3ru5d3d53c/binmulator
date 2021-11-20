cmake_minimum_required(VERSION 3.16.3)

project(binmulator)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} -lunicorn -lpthread)
