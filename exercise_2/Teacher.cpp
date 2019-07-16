#include <sstream>
#include "Teacher.h"

constexpr const char Teacher::RECORD_PREFIX;

Teacher::Teacher(int id, std::string name) : _id{id}, _name{std::move(name)} {}

std::string Teacher::get_name() const {
    return _name;
}

int Teacher::get_id() const {
    return _id;
}

std::string Teacher::get_formatted() const {
    std::ostringstream oss;
    oss << _id << " " << _name << std::endl;
    return oss.str();

}