cmake_minimum_required(VERSION 3.14)
project(exercise_3)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SRC_FILES *.cpp)

add_executable(exercise_3 ${SRC_FILES})

target_compile_options(exercise_3 PRIVATE -Wall -Wextra -Werror)