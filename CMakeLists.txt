cmake_minimum_required(VERSION 3.14)

project("algs-and-ds")

file(GLOB_RECURSE PROJECT_SOURCES "src/*")
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
