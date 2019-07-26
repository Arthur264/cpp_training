#include <iostream>
#include "RecordFactory.h"

std::shared_ptr<Record> CourseFactory::create(std::stringstream &stream) const {
    auto id = record::parse_parameter<int>(stream);
    auto name = record::parse_parameter<std::string>(stream);
    auto teacher_id = record::parse_parameter<int>(stream);
    return std::make_shared<Course>(id, name, teacher_id);
}


std::shared_ptr<Record> ExamFactory::create(std::stringstream &stream) const {
    auto id = record::parse_parameter<int>(stream);
    auto course_id = record::parse_parameter<int>(stream);
    auto student_id = record::parse_parameter<int>(stream);
    auto result = record::parse_parameter<int>(stream);
    return std::make_shared<Exam>(id, course_id, student_id, result);
}


std::shared_ptr<Record> StudentFactory::create(std::stringstream &stream) const {
    auto id = record::parse_parameter<int>(stream);
    auto name = record::parse_parameter<std::string>(stream);
    return std::make_shared<Student>(id, name);
}


std::shared_ptr<Record> TeacherFactory::create(std::stringstream &stream) const {
    auto id = record::parse_parameter<int>(stream);
    auto name = record::parse_parameter<std::string>(stream);
    return std::make_shared<Teacher>(id, name);
}
