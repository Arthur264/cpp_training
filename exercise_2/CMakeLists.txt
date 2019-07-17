cmake_minimum_required(VERSION 3.14)
project(exercise_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(exercise_2 main.cpp RecordStorage.cpp Course.cpp Exam.cpp Student.cpp Teacher.cpp Record.cpp Person.cpp)