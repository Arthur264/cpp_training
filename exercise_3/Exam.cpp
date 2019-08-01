#include <sstream>
#include "Exam.h"

constexpr const char Exam::RECORD_PREFIX;
const std::string Exam::TABLE_NAME = "EXAM";

Exam::Exam(int id, int course_id, int student_id, int result) : Record{id}, _course_id{course_id},
                                                                _student_id{student_id},
                                                                _result{result} {}


record::PropMap Exam::get_int_props() {
    return record::PropMap{
            {"CourseId",  &_course_id},
            {"StudentId", &_student_id},
            {"Result",    &_result}
    };
}

bool Exam::match(const record::CompareParam &compare_param) const {
    return match_int(compare_param);
}

void Exam::update(const record::CompareParam &compare_param) {
    validation_update(compare_param.name);
    update_int(compare_param);
}

std::string Exam::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << _course_id << " " << _student_id << " " << _result << std::endl;
    return oss.str();

}

std::string Exam::get_pretty_printed() const {
    std::ostringstream oss;
    oss << "ID: " << get_id() << ", "
        << "CourseId: " << _course_id << ", "
        << "StudentId: " << _student_id << ", "
        << "Result: " << _result << std::endl;
    return oss.str();

}