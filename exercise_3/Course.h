#pragma once

#include <string>
#include <map>
#include <functional>
#include "Record.h"

class Course : public Record {
public:
    static constexpr const char RECORD_PREFIX = 'C';
    static const std::string TABLE_NAME;

    Course(int id, std::string name, int teacher_id);

    std::string get_formatted() const override;

    std::string get_pretty_printed() const override;

    bool match(const record::CompareParam &compare_param) const override;

    void update(const record::CompareParam &compare_param) override;

private:
    std::string _name;
    int _teacher_id;

    record::PropMap get_int_props() override;
};