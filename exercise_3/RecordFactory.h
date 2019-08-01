#pragma once

#include <memory>
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include "Exam.h"
#include "Record.h"

class IRecordFactory {
public:
    virtual std::unique_ptr<Record> create(std::stringstream &stream) const = 0;
};


class CourseFactory : public IRecordFactory {
public:
    std::unique_ptr<Record> create(std::stringstream &stream) const override;
};


class ExamFactory : public IRecordFactory {
public:
    std::unique_ptr<Record> create(std::stringstream &stream) const override;
};


class StudentFactory : public IRecordFactory {
public:
    std::unique_ptr<Record> create(std::stringstream &stream) const override;
};

class TeacherFactory : public IRecordFactory {
public:
    std::unique_ptr<Record> create(std::stringstream &stream) const override;
};

namespace record {
    using RecordFactories = std::unordered_map<char, std::unique_ptr<IRecordFactory>>;
}