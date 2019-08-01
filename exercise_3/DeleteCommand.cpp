#include <algorithm>
#include "DeleteCommand.h"

const std::string DeleteCommand::COMMAND_REGEX_CONDITION = "^DELETE (.+) WHERE (.+);";

DeleteCommand::DeleteCommand(RecordStorage &record_storage, const std::string &table_name,
                             const std::vector<record::CompareParam> &command_params) :
        Command{record_storage, table_name, command_params} {
}

void DeleteCommand::execute() {
    int deleted_rows = 0;
    auto &records = record_storage.get_records(table_name);
    auto command_params_copy = command_params;
    auto match_records = [&deleted_rows, command_params_copy](const std::shared_ptr<Record> &record) {
        for (const auto &command_param: command_params_copy) {
            if (!record->match(command_param)) {
                return false;
            }
        }
        ++deleted_rows;
        return true;
    };
    auto it = std::remove_if(records.begin(), records.end(), match_records);
    records.erase(it, records.end());

    std::cout << "Deleted rows in table " << table_name << ": " << deleted_rows << std::endl;
}
