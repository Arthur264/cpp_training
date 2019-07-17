#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Record.h"
#include "RecordStorage.h"
#include "Student.h"
#include "Course.h"
#include "Exam.h"
#include "Teacher.h"

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

std::shared_ptr<Record> record_factory(char &record_type, const std::string &row) {
    std::stringstream stream(row);
    record_type = parse_parameter<char>(stream);
    auto id = parse_parameter<int>(stream);
    switch (record_type) {
        case Student::RECORD_PREFIX: {
            auto name = parse_parameter<std::string>(stream);
            return std::make_shared<Student>(id, name);
        }
        case Course::RECORD_PREFIX: {
            auto name = parse_parameter<std::string>(stream);
            auto teacher_id = parse_parameter<int>(stream);
            return std::make_shared<Course>(id, name, teacher_id);
        }
        case Exam::RECORD_PREFIX: {
            auto course_id = parse_parameter<int>(stream);
            auto student_id = parse_parameter<int>(stream);
            auto result = parse_parameter<int>(stream);
            return std::make_shared<Exam>(id, course_id, student_id, result);
        }
        case Teacher::RECORD_PREFIX: {
            auto name = parse_parameter<std::string>(stream);
            return std::make_shared<Teacher>(id, name);
        }
        default:
            exit(EXIT_FAILURE);
    }
}

void load_records_from_file(const std::string &file_path, RecordStorage &record_storage) {
    char record_type;
    std::string line;
    std::ifstream infile(file_path);

    if (infile.fail()) {
        std::cerr << "File not exist" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (std::getline(infile, line)) {
        auto record_ptr = record_factory(record_type, line);
        record_storage.add(record_type, record_ptr);
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Please pass path to records file" << std::endl;
        return EXIT_FAILURE;
    }
    record::FilePathMap file_path_map = {
            {Student::RECORD_PREFIX, "student.txt"},
            {Course::RECORD_PREFIX,  "course.txt"},
            {Teacher::RECORD_PREFIX, "teacher.txt"},
            {Exam::RECORD_PREFIX,    "exam.txt"},
    };
    RecordStorage record_storage(file_path_map);

    std::cout << "Load records from file" << std::endl;
    load_records_from_file(argv[1], record_storage);

    std::cout << "Write records in different files" << std::endl;
    record_storage.dumps();

    return EXIT_SUCCESS;
}