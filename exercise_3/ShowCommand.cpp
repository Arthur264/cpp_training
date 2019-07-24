#include <iostream>
#include "ShowCommand.h"

const std::string ShowCommand::COMMAND_REGEX("SHOW (.+)");
const std::string ShowCommand::COMMAND_REGEX_CONDITION("SHOW (.+) WHERE (.+);");

ShowCommand::ShowCommand(const RecordStorage &record_storage, const std::string &table_name,
                         const std::vector<cmd::CommandParam> &command_params) :
        Command(record_storage, table_name, command_params) {}

void ShowCommand::execute() {
    record::RecordMap record_map = record_storage.get_record_map();
    if (table_name == "*") {
        for (const auto &it: record_map) {
            _print_table(it.first, record_map);
        }
    } else {
        _print_table(table_name, record_map);
    }
}

record::RecordVectorPtr ShowCommand::_filter_records(record::RecordVectorPtr records) const {
    record::RecordVectorPtr filtered_records;
    for (const auto &command_param: command_params) {
        auto comparison = Command::comparisons_map.find(command_param.comparison);
        if (Command::comparisons_map.end() == comparison) {
            throw std::invalid_argument("Invalid comparison expression");
        }
        auto comparison_func = comparison -> second;
        auto compare_records = [comparison_func, &command_param](const std::shared_ptr<Record> &record) -> bool {
            return comparison_func(record->get_id(), command_param.value) == 1;
        };
        std::copy_if(records.begin(), records.end(), std::back_inserter(filtered_records), compare_records);
    }
    return filtered_records;
}

bool ShowCommand::_print_table(const std::string &table_name, const record::RecordMap &record_map) const {
    auto it = record_map.find(table_name);
    std::cout << table_name << std::endl;
    if (it == record_map.end()) {
        std::cerr << "Table " << table_name << " not found." << std::endl;
        return false;
    }

    std::cout << "Table " << table_name << ":" << std::endl;
    for (const auto &record: _filter_records(it->second)) {
        std::cout << record->get_pretty_printed();
    }
    std::cout << std::endl;
    return true;
}
