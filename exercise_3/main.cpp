#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "RecordFactory.h"
#include "RecordStorage.h"
#include "Invoker.h"
#include "Command.h"
#include "ShowCommand.h"
#include "DeleteCommand.h"
#include "UpdateCommand.h"

constexpr char STOP_LETTER = 'q';

std::shared_ptr<Record>
record_factory(char &record_type, const std::string &row, const record::RecordFactories &recordFactories) {
    std::stringstream stream(row);
    record_type = record::parse_parameter<char>(stream);
    auto it = recordFactories.find(record_type);
    if (it == recordFactories.end()) {
        exit(EXIT_FAILURE);
    }
    return it->second->create(stream);
}

void load_records_from_file(const std::string &file_path, RecordStorage &record_storage) {
    char record_type;
    std::string line;
    std::ifstream infile(file_path);
    record::RecordFactories recordFactories = {
            {Student::RECORD_PREFIX, std::make_shared<StudentFactory>()},
            {Course::RECORD_PREFIX,  std::make_shared<CourseFactory>()},
            {Teacher::RECORD_PREFIX, std::make_shared<TeacherFactory>()},
            {Exam::RECORD_PREFIX,    std::make_shared<ExamFactory>()},
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


void command_parse(const std::string &command_line, cmd::CommandMap &command_map, Invoker &inv) {
    std::smatch matches;
    bool is_match = false;
    for (const auto &it: command_map) {
        if (std::regex_search(command_line, matches, std::regex(it.first)) && matches.size() > 1) {
            try {
                (inv.*it.second)(matches);
            } catch (std::invalid_argument &e) {
                std::cerr << "Invalid command argument: " << e.what() << std::endl;
            }
            is_match = true;
            break;
        }
    }
    if (!is_match) {
        std::cerr << "Invalid command, please try again" << std::endl;
    }
}

int main(int argc, char **argv) {
    if (argc == 1) {
        std::cerr << "Please pass path to records file" << std::endl;
        return EXIT_FAILURE;
    }

    std::string command_line;
    record::StorageMap storage_map = {
            {Student::RECORD_PREFIX, {"student.txt", Student::TABLE_NAME}},
            {Course::RECORD_PREFIX,  {"course.txt",  Course::TABLE_NAME}},
            {Teacher::RECORD_PREFIX, {"teacher.txt", Teacher::TABLE_NAME}},
            {Exam::RECORD_PREFIX,    {"exam.txt",    Exam::TABLE_NAME}},
    };
    RecordStorage record_storage(storage_map);

    std::cout << "Load records from file" << std::endl;
    load_records_from_file(argv[1], record_storage);

    Invoker inv(record_storage);
    CommandParser command_parser;

    inv.set_parser(command_parser);

    cmd::CommandMap command_map = {
            {ShowCommand::COMMAND_REGEX_CONDITION,   &Invoker::show_condition_records},
//            {ShowCommand::COMMAND_REGEX,             &Invoker::show_records},
            {DeleteCommand::COMMAND_REGEX_CONDITION, &Invoker::delete_record},
            {UpdateCommand::COMMAND_REGEX_CONDITION, &Invoker::update_record},
    };

    std::cout << "Please write a command below: " << std::endl;
    while (std::getline(std::cin, command_line)) {
        if (command_line.size() == 1 && STOP_LETTER == command_line[0]) {
            break;
        }
        command_parse(command_line, command_map, inv);
    }

    std::cout << "Write records in different files" << std::endl;
    record_storage.dumps();

    return EXIT_SUCCESS;
}