#include <sstream>
#include "Teacher.h"

constexpr const char Teacher::RECORD_PREFIX;
const std::string Teacher::TABLE_NAME = "TEACHER";

Teacher::Teacher(int id, std::string name) : Record(id), Person(std::move(name)) {}

record::PropMap Teacher::get_int_props() {
    return record::PropMap{};
}

bool Teacher::match(const record::CompareParam &compare_param) const {
    if (compare_param.name == "Name") {
        return _name == compare_param.value;
    }
    return match_int(compare_param);
}

void Teacher::update(const record::CompareParam &compare_param) {
    std::stringstream stream(compare_param.value);
    validation_update(compare_param.name);
    if (compare_param.name == "Name") {
        _name = compare_param.value;
    } else {
        throw std::invalid_argument("Error parse conditions params");
    }
}

std::string Teacher::get_formatted() const {
    std::ostringstream oss;
    oss << get_id() << " " << get_name() << std::endl;
    return oss.str();
}

std::string Teacher::get_pretty_printed() const {
    std::ostringstream oss;
    oss << "ID: " << get_id() << ", "
        << "Name: " << get_name() << std::endl;
    return oss.str();

}