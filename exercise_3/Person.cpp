#include "Person.h"

Person::Person(const std::string &name) : _name{name} {}

std::string Person::get_name() const {
    return _name;
}
