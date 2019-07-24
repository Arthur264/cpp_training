#pragma once

#include <memory>
#include "Course.h"
#include "Student.h"
#include "Teacher.h"
#include "Exam.h"
#include "Record.h"

class IRecordFactory {
public:
    virtual std::shared_ptr<Record> create(std::stringstream &stream) const = 0;
};


class CourseFactory : public IRecordFactory {
public:
    std::shared_ptr<Record> create(std::stringstream &stream) const override;
};


class ExamFactory : public IRecordFactory {
public:
    std::shared_ptr<Record> create(std::stringstream &stream) const override;
};


class StudentFactory : public IRecordFactory {
public:
    std::shared_ptr<Record> create(std::stringstream &stream) const override;
};

class TeacherFactory : public IRecordFactory {
public:
    std::shared_ptr<Record> create(std::stringstream &stream) const override;
};

namespace record {
    using RecordFactories = std::unordered_map<char, std::shared_ptr<IRecordFactory>>;

    template<class T>
    T parse_parameter(std::stringstream &stream) {
        T buffer;
        std::string tmp;
        if (!std::getline(stream, tmp, ',')) {
            std::cerr << "Parse args failure" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::stringstream ss(tmp);
        ss >> buffer;
        return buffer;
    }
}