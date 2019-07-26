#include <sstream>
#include "Student.h"

constexpr const char Student::RECORD_PREFIX;
const std::string Student::TABLE_NAME = "STUDENT";

Student::Student(int id, std::string name) : Record(id), Person(std::move(name)) {}


record::PropMap Student::get_int_props() {
    return record::PropMap{};
}

bool Student::match(const record::CompareParam &compare_param) const {
    if (compare_param.name == "Name") {
        validation_string(compare_param);
        return _name == compare_param.value;
    }
    return match_int(compare_param);
}

void Student::update(const record::CompareParam &compare_param) {
    std::stringstream stream(compare_param.value);
    validation_update(compare_param.name);
    if (compare_param.name == "Name") {
        _name = compare_param.value;
    } else {
        throw std::invalid_argument("Error parse conditions params");
    }
}

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