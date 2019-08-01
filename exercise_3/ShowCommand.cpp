#include <iostream>
#include "ShowCommand.h"

const std::string ShowCommand::COMMAND_REGEX("^SHOW (.+);");
const std::string ShowCommand::COMMAND_REGEX_CONDITION("^SHOW (.+) WHERE (.+);");

ShowCommand::ShowCommand(RecordStorage &record_storage, const std::string &table_name,
                         const std::vector<record::CompareParam> &command_params) :
        Command{record_storage, table_name, command_params} {
}

void ShowCommand::execute() {
    if (table_name == "*") {
        const auto record_map = record_storage.get_record_map();
        for (const auto &it: record_map) {
            _print_table(it.first);
        }
    } else {
        _print_table(table_name);
    }
}

bool ShowCommand::_print_table(const std::string &table_name) {
    const auto &records = record_storage.get_records(table_name);
    std::cout << "Table " << table_name << ":" << std::endl;
    const auto filtered_records = _filter_records(records);
    if (filtered_records.empty()) {
        std::cerr << "No matches found" << std::endl;
        return false;
    }
    for (const auto &record: filtered_records) {
        std::cout << record->get_pretty_printed();
    }
    std::cout << std::endl;
    return true;
}


record::RecordVectorPtr ShowCommand::_filter_records(const record::RecordVectorPtr &records) const {
    if (command_params.empty()) {
        return records;
    }

    record::RecordVectorPtr filtered_records;
    for (const auto &record: records) {
        auto compare_records = [&record](const record::CompareParam &command_param) {
            return record->match(command_param);
        };
        if (std::all_of(command_params.begin(), command_params.end(), compare_records)) {
            filtered_records.emplace_back(record);
        }
    }
    return filtered_records;
}