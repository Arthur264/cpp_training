#pragma once

#include <regex>
#include <vector>
#include "Command.h"
#include "CommandParser.h"

class Invoker {
public:
    explicit Invoker(RecordStorage &&record_storage);

    void delete_record(const std::smatch &matches);

    void show_records(const std::smatch &matches);

    void show_condition_records(const std::smatch &matches);

    void update_record(const std::smatch &matches);

    void set_parser(const CommandParser &command_parser);

private:
    std::shared_ptr<Command> _command;
    RecordStorage &_record_storage;
    CommandParser _command_parser;
};

namespace cmd {
    typedef void(Invoker::*InvokerFunc)(const std::smatch &);

    using CommandMap = std::map<std::string, InvokerFunc>;
}