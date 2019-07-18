#pragma once

#include <string>
#include "Record.h"
#include "Person.h"

class Student : public Record, public Person {
public:
    static constexpr const char RECORD_PREFIX = 'S';

    Student(int id, std::string name);

    std::string get_formatted() const override;
};