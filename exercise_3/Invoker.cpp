#include "Invoker.h"
#include "UpdateCommand.h"
#include "ShowCommand.h"
#include "DeleteCommand.h"


Invoker::Invoker(RecordStorage &&record_storage) : _record_storage{record_storage} {}

void Invoker::delete_record(const std::smatch &matches) {
    const auto param_str = matches.str(2);
    const auto command_params = _command_parser.parse_expression(param_str);
    const auto table_name = matches.str(1);
    DeleteCommand command(_record_storage, table_name, command_params);
    command.execute();
}


void Invoker::show_records(const std::smatch &matches) {
    const auto table_name = matches.str(1);
    ShowCommand command(_record_storage, table_name);
    command.execute();
}

void Invoker::show_condition_records(const std::smatch &matches) {
    const auto param_str = matches.str(2);
    const auto command_params = _command_parser.parse_expression(param_str);
    const auto table_name = matches.str(1);
    ShowCommand command(_record_storage, table_name, command_params);
    command.execute();
}


void Invoker::update_record(const std::smatch &matches) {
    const auto param_str = matches.str(2);
    const auto update_str = matches.str(3);
    const auto command_params = _command_parser.parse_expression(update_str);
    const auto table_name = matches.str(1);
    const auto update_param = _command_parser.parse_update_param(param_str);
    UpdateCommand command(_record_storage, table_name, command_params, update_param);
    command.execute();
}


void Invoker::set_parser(const CommandParser &command_parser) {
    _command_parser = command_parser;
}