#include "Invoker.h"
#include "UpdateCommand.h"
#include "ShowCommand.h"
#include "DeleteCommand.h"


Invoker::Invoker(RecordStorage &&record_storage) : _record_storage{record_storage} {}

void Invoker::delete_record(const std::smatch &matches) {
    auto param_str = matches.str(2);
    auto command_params = _command_parser.parse_expression(param_str);
    auto table_name = matches.str(1);
    _command = std::make_shared<DeleteCommand>(_record_storage, table_name, command_params);
    _command->execute();
}


void Invoker::show_records(const std::smatch &matches) {
    auto table_name = matches.str(1);
    _command = std::make_shared<ShowCommand>(_record_storage, table_name);
    _command->execute();
}

void Invoker::show_condition_records(const std::smatch &matches) {
    auto param_str = matches.str(2);
    auto command_params = _command_parser.parse_expression(param_str);
    auto table_name = matches.str(1);
    _command = std::make_shared<ShowCommand>(_record_storage, table_name, command_params);
    _command->execute();
}


void Invoker::update_record(const std::smatch &matches) {
    auto param_str = matches.str(2);
    auto update_str = matches.str(3);
    auto command_params = _command_parser.parse_expression(update_str);
    auto table_name = matches.str(1);
    auto update_param = _command_parser.parse_update_param(param_str);
    _command = std::make_shared<UpdateCommand>(_record_storage, table_name, command_params, update_param);
    _command->execute();
}


void Invoker::set_parser(const CommandParser &command_parser) {
    _command_parser = command_parser;
}