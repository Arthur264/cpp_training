#pragma once

#include <string>
#include "Record.h"

class Course : public Record {
public:
    static constexpr const char RECORD_PREFIX = 'C';

    Course(int id, std::string name, int teacher_id);

    std::string get_formatted() const override;

private:
    const std::string _name;    const int _teacher_id;
};