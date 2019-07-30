#include "Record.h"

Record::Record(int id) : _id{id} {}

int Record::get_id() const {
    return _id;
}

void Record::validation_update(const std::string &name) const {
    if (name == "Id") {
        throw std::invalid_argument("Id can`t by updated");
    }
}

bool Record::match_int(const record::CompareParam &compare_param) const {
    std::stringstream stream(compare_param.value);
    auto value = record::parse_parameter<int>(stream);
    if (compare_param.name == "Id") {
        return compare_param.comparison(_id, value);
    }
    const auto props = const_cast<Record *>(this)->get_int_props();
    auto it = props.find(compare_param.name);
    if (it == props.end()) {
        throw std::invalid_argument("Error parse conditions params");
    }
    return compare_param.comparison(*it->second, value);
}


void Record::update_int(const record::CompareParam &compare_param) {
    std::stringstream stream(compare_param.value);
    auto props = get_int_props();
    auto it = props.find(compare_param.name);
    if (it == props.end()) {
        throw std::invalid_argument("Error parse conditions params");
    }
    *it->second = record::parse_parameter<int>(stream);
}

void Record::validation_string(const record::CompareParam &compare_param) const {
    if (compare_param.comparison_sign != "=") {
        throw std::invalid_argument("String attributes support only equal to operator");
    }
}