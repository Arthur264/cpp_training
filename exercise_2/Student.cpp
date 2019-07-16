#include <sstream>
#include "Student.h"

constexpr const char Student::RECORD_PREFIX;

Student::Student(int id, std::string name) : _id{id}, _name{std::move(name)} {}


std::string Student::get_name() const {
    return _name;
}

int Student::get_id() const {
    return _id;
}

std::string Student::get_formatted() const {
    std::ostringstream oss;
    oss << _id << " " << _name << std::endl;
    return oss.str();

}