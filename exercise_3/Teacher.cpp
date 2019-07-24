#include <sstream>
#include "Teacher.h"

constexpr const char Teacher::RECORD_PREFIX;
const std::string Teacher::TABLE_NAME = "TEACHER";

Teacher::Teacher(int id, std::string name) : Record(id), Person(std::move(name)) {}


std::string Teacher::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << get_name() << std::endl;
    return oss.str();
}

std::string Teacher::get_pretty_printed() const {
    std::ostringstream oss;
    oss << "ID: " << get_id()
        << ", Name: " << get_name() << std::endl;
    return oss.str();

}