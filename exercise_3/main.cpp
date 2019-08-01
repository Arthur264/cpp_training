#include <iostream>
#include "RecordFactory.h"
#include "RecordStorage.h"
#include "Invoker.h"
#include "ShowCommand.h"
#include "DeleteCommand.h"
#include "UpdateCommand.h"

constexpr char STOP_LETTER = 'q';

std::shared_ptr<Record>
record_factory(char &record_type, const std::string &row, const record::RecordFactories &recordFactories) {
    std::stringstream stream(row);
    record_type = record::parse_parameter<char>(stream);
    const auto &it = recordFactories.find(record_type);
    if (it == recordFactories.end()) {
        std::cerr << "Unknown record type" << std::endl;
        exit(EXIT_FAILURE);
    }
    return it->second->create(stream);
}

void load_records_from_file(const std::string &file_path, RecordStorage &record_storage) {
    std::ifstream infile(file_path);
    if (infile.fail()) {
        std::cerr << "File not exist" << std::endl;
        exit(EXIT_FAILURE);
    }

    char record_type;
    std::string line;

    record::RecordFactories recordFactories{};
    recordFactories[Student::RECORD_PREFIX] = std::make_unique<StudentFactory>();
    recordFactories[Course::RECORD_PREFIX] = std::make_unique<CourseFactory>();
    recordFactories[Teacher::RECORD_PREFIX] = std::make_unique<TeacherFactory>();
    recordFactories[Exam::RECORD_PREFIX] = std::make_unique<ExamFactory>();


    while (std::getline(infile, line)) {
        auto record_ptr = record_factory(record_type, line, recordFactories);
        record_storage.add(record_type, record_ptr);
    }
}


bool command_parse(const std::string &command_line, const cmd::CommandMap &command_map, Invoker &inv) {
    std::smatch matches;
    auto command_match = [&command_line, &matches](const auto &it) {
        return std::regex_search(command_line, matches, std::regex(it.first)) && matches.size() > 1;
    };
    auto command = std::find_if(command_map.begin(), command_map.end(), command_match);
    if (command == command_map.end()) {
        std::cerr << "Invalid command, please try again" << std::endl;
        return false;
    }
    try {
        (inv.*command->second)(matches);
    } catch (std::invalid_argument &e) {
        std::cerr << "Invalid command argument: " << e.what() << std::endl;
        return false;
    }
    return true;
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

    Invoker inv(std::move(record_storage));
    CommandParser command_parser;

    inv.set_parser(command_parser);

    cmd::CommandMap command_map = {
            {ShowCommand::COMMAND_REGEX_CONDITION,   &Invoker::show_condition_records},
            {ShowCommand::COMMAND_REGEX,             &Invoker::show_records},
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