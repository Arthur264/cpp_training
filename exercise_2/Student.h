#pragma once

#include <string>
#include "Person.h"
#include "Record.h"

class Student : public Person, public Record {
public:
    static constexpr const char RECORD_PREFIX = 'S';

    Student(int id, std::string name);

    std::string get_formatted() const override;
};