cmake_minimum_required(VERSION 3.14)
project(exercise_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(exercise_2 main.cpp Course.h Teacher.h Student.h Exam.h IRecord.h IPerson.h RecordStorage.h RecordStorage.cpp Course.cpp Exam.cpp Student.cpp Teacher.cpp)