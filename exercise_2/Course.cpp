#include <sstream>
#include "Course.h"

constexpr const char Course::RECORD_PREFIX;

Course::Course(int id, std::string name, int teacher_id) : _id{id}, _name{std::move(name)}, _teacher_id{teacher_id} {}

int Course::get_id() const {
    return _id;
}

std::string Course::get_formatted() const {
    std::ostringstream oss;
    oss << _id << " " << _name << " " << _teacher_id << std::endl;
    return oss.str();

}