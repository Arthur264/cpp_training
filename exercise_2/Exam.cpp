#include <sstream>
#include "Exam.h"

constexpr const char Exam::RECORD_PREFIX;

Exam::Exam(int id, int course_id, int student_id, int result) : Record(id), _course_id{course_id}, _student_id{student_id},
                                                                _result{result} {}

std::string Exam::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << _course_id << " " << _student_id << " " << _result << std::endl;
    return oss.str();

}