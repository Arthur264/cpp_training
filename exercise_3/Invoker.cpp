#include <iostream>
#include "Invoker.h"
#include "UpdateCommand.h"
#include "ShowCommand.h"
#include "DeleteCommand.h"


Invoker::Invoker(const RecordStorage &record_storage) : _record_storage{record_storage} {}

void Invoker::delete_record(const std::smatch &matches) {
    auto command_params = _command_parser.parse_expression(matches.str(2));
    auto table_name = matches.str(1);
    _command = std::make_shared<DeleteCommand>(_record_storage, table_name, command_params);
    _command->execute();
}


void Invoker::show_records(const std::smatch &matches) {
    std::cout << matches.str(1) << std::endl;
//    _command = std::make_shared<ShowCommand>(_record_storage, matches.str(1));
//    _command->execute();
}

void Invoker::show_condition_records(const std::smatch &matches) {
    auto command_params = _command_parser.parse_expression(matches.str(2));
    auto table_name = matches.str(1);
    _command = std::make_shared<ShowCommand>(_record_storage, table_name, command_params);
    _command->execute();
}


void Invoker::update_record(const std::smatch &matches) {
    auto command_params = _command_parser.parse_expression(matches.str(2));
    auto table_name = matches.str(1);
    _command = std::make_shared<UpdateCommand>(_record_storage, table_name, command_params);
    _command->execute();
}


void Invoker::set_parser(const CommandParser &command_parser) {
    _command_parser = command_parser;
}