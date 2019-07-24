#pragma once

#include "Record.h"

class Exam : public Record {
public:
    static constexpr const char RECORD_PREFIX = 'E';
    static const std::string TABLE_NAME;

    Exam(int id, int course_id, int student_id, int result);

    std::string get_formatted() const override;

    std::string get_pretty_printed() const override;


private:
    const int _course_id;
    const int _student_id;
    const int _result;
};