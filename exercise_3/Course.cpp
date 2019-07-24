#include <sstream>
#include "Course.h"

constexpr const char Course::RECORD_PREFIX;
const std::string Course::TABLE_NAME = "COURSE";
//constexpr const  std::unordered_map<std::string, int> Course::PROPERTIES = std::unordered_map<std::string, int>(
//        {"ID", &Course::get_id()},
//        {"TeacherID", &Course::teacher_id},
//);

Course::Course(int id, std::string name, int teacher_id) : Record(id), _name{std::move(name)},
                                                           _teacher_id{teacher_id} {}


std::string Course::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << _name << " " << _teacher_id << std::endl;
    return oss.str();

}

std::string Course::get_pretty_printed() const {
    std::ostringstream oss;
    oss << "ID: " << get_id() << ", "
        << "Name: " << _name << ", "
        << "TeacherID: " << _teacher_id << std::endl;
    return oss.str();

}