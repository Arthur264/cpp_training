#pragma once

#include <string>

class Person {
public:
    Person(std::string name);

    std::string get_name() const;

    virtual ~Person() = default;

protected:
    std::string _name;
};