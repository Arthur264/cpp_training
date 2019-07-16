#pragma once

#include <string>
#include "IRecord.h"

class Course : public IRecord {
public:
    static constexpr const char RECORD_PREFIX = 'C';

    Course(int id, std::string name, int teacher_id);

    int get_id() const override;

    std::string get_formatted() const override;

private:
    const int _id;
    const std::string _name;
    const int _teacher_id;
};