#pragma once

#include <string>
#include "Record.h"
#include "Person.h"

class Student : public Record, public Person {
public:
    static constexpr const char RECORD_PREFIX = 'S';
    static const std::string TABLE_NAME;

    Student(int id, const std::string &name);

    std::string get_formatted() const override;

    std::string get_pretty_printed() const override;

    bool match(const record::CompareParam &compare_param) const override;

    void update(const record::CompareParam &compare_param) override;

private:
    record::PropMap get_int_props() override;
};