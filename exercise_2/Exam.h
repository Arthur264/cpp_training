#pragma once

#include "IRecord.h"

class Exam : public IRecord {
public:
    static constexpr const char RECORD_PREFIX = 'E';

    Exam(int id, int course_id, int student_id, int result);

    int get_id() const override;

    std::string get_formatted() const override;


private:
    const int _id;
    const int _course_id;
    const int _student_id;
    const int _result;
};