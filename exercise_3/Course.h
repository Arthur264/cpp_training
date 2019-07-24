#pragma once

#include <string>
#include "Record.h"

class Course : public Record {
public:
    static constexpr const char RECORD_PREFIX = 'C';
    static const std::string TABLE_NAME;
//    static constexpr const  std::unordered_map<std::string, int> PROPERTIES;

    Course(int id, std::string name, int teacher_id);

    std::string get_formatted() const override;

    std::string get_pretty_printed() const override;

private:
    const std::string _name;
    const int _teacher_id;
};