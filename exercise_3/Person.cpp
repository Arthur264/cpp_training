#include "Person.h"

Person::Person(std::string name) : _name{std::move(name)} {}

std::string Person::get_name() const {
    return _name;
}
