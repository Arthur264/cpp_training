#include <sstream>
#include "Course.h"

constexpr const char Course::RECORD_PREFIX;
const std::string Course::TABLE_NAME = "COURSE";

Course::Course(int id, std::string name, int teacher_id) : Record(id), _name{std::move(name)},
                                                           _teacher_id{teacher_id} {}


record::PropMap Course::get_int_props() {
    return record::PropMap{
            {"TeacherID", &_teacher_id}
    };
}

bool Course::match(const record::CompareParam &compare_param) const {
    if (compare_param.name == "Name") {
        return _name == compare_param.value;
    }
    return match_int(compare_param);
}

void Course::update(const record::CompareParam &compare_param) {
    std::stringstream stream(compare_param.value);
    validation_update(compare_param.name);
    if (compare_param.name == "Name") {
        _name = compare_param.value;
    } else {
        update_int(compare_param);
    }
}

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