#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "RecordFactory.h"
#include "RecordStorage.h"


std::shared_ptr<Record>
record_factory(char &record_type, const std::string &row, const record::RecordFactories &recordFactories) {
    std::stringstream stream(row);
    record_type = record::parse_parameter<char>(stream);
    auto it = recordFactories.find(record_type);
    if (it == recordFactories.end()) {
        exit(EXIT_FAILURE);
    }
    IRecordFactory *factory = it->second;
    return factory->create(stream);

}

void load_records_from_file(const std::string &file_path, RecordStorage &record_storage) {
    char record_type;
    std::string line;
    std::ifstream infile(file_path);
    record::RecordFactories recordFactories = {
            {Student::RECORD_PREFIX, new StudentFactory()},
            {Course::RECORD_PREFIX,  new CourseFactory()},
            {Teacher::RECORD_PREFIX, new TeacherFactory()},
            {Exam::RECORD_PREFIX,    new ExamFactory()},
    };

    if (infile.fail()) {
        std::cerr << "File not exist" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (std::getline(infile, line)) {
        auto record_ptr = record_factory(record_type, line, recordFactories);
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