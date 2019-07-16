#include <sstream>
#include "Exam.h"

constexpr const char Exam::RECORD_PREFIX;

Exam::Exam(int id, int course_id, int student_id, int result) : _id{id}, _course_id{course_id}, _student_id{student_id},
                                                                _result{result} {}

int Exam::get_id() const {
    return _id;

}

std::string Exam::get_formatted() const {
    std::ostringstream oss;
    oss << _id << " " << _course_id << " " << _student_id << " " << _result << std::endl;
    return oss.str();

}