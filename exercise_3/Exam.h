#pragma once

#include "Record.h"

class Exam : public Record {
public:
    static constexpr const char RECORD_PREFIX = 'E';
    static const std::string TABLE_NAME;

    Exam(int id, int course_id, int student_id, int result);

    std::string get_formatted() const override;

    std::string get_pretty_printed() const override;

    bool match(const record::CompareParam &compare_param) const override;

    void update(const record::CompareParam &compare_param) override;

private:
    int _course_id;
    int _student_id;
    int _result;

    record::PropMap get_int_props() override;
};