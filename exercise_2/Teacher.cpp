#include <sstream>
#include "Teacher.h"

constexpr const char Teacher::RECORD_PREFIX;

Teacher::Teacher(int id, std::string name) : Record(id), Person(std::move(name)) {}


std::string Teacher::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << get_name() << std::endl;
    return oss.str();

}