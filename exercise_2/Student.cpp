#include <sstream>
#include "Student.h"

constexpr const char Student::RECORD_PREFIX;

Student::Student(int id, std::string name) : Record(id), Person(std::move(name)) {}

std::string Student::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << get_name() << std::endl;
    return oss.str();

}