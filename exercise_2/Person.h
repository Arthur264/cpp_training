#pragma once

#include <string>

class Person {
public:
    explicit Person(std::string name);

    std::string get_name() const;

    virtual ~Person() = default;

protected:
    const std::string _name;
};