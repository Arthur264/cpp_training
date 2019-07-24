#include <sstream>
#include "Student.h"

constexpr const char Student::RECORD_PREFIX;
const std::string Student::TABLE_NAME = "STUDENT";

Student::Student(int id, std::string name) : Record(id), Person(std::move(name)) {}

std::string Student::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << get_name() << std::endl;
    return oss.str();

}

std::string Student::get_pretty_printed() const {
    std::ostringstream oss;
    oss << "ID: " << get_id() << ", "
        << "Name: " << get_name() << std::endl;
    return oss.str();

}