#pragma once

#include <string>
#include "Person.h"
#include "Record.h"

class Teacher : public Person, public Record {
public:
    static constexpr const char RECORD_PREFIX = 'T';

    Teacher(int id, std::string name);

    std::string get_formatted() const override;

private:
    const std::string _name;
};