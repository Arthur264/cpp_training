#include <sstream>
#include "Course.h"

constexpr const char Course::RECORD_PREFIX;

Course::Course(int id, std::string name, int teacher_id) : Record(id), _name{std::move(name)}, _teacher_id{teacher_id} {}


std::string Course::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << _name << " " << _teacher_id << std::endl;
    return oss.str();

}