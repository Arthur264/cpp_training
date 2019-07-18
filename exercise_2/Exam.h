#pragma once

#include "Record.h"

class Exam : public Record {
public:
    static constexpr const char RECORD_PREFIX = 'E';

    Exam(int id, int course_id, int student_id, int result);

    std::string get_formatted() const override;


private:
    const int _course_id;
    const int _student_id;
    const int _result;
};