#pragma once

#include <string>
#include "Person.h"
#include "Record.h"

class Teacher : public Record, public Person {
public:
    static constexpr const char RECORD_PREFIX = 'T';
    static const std::string TABLE_NAME;

    Teacher(int id, const std::string &name);

    std::string get_formatted() const override;

    std::string get_pretty_printed() const override;

    bool match(const record::CompareParam &compare_param) const override;

    void update(const record::CompareParam &compare_param) override;

private:
    record::PropMap get_int_props() override;
};