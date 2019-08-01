#include "UpdateCommand.h"

const std::string UpdateCommand::COMMAND_REGEX_CONDITION("^UPDATE (\\w+) (.+) WHERE (.+);");

UpdateCommand::UpdateCommand(RecordStorage &record_storage, const std::string &table_name,
                             const std::vector<record::CompareParam> &command_params,
                             const record::CompareParam &update_param) :
        Command{record_storage, table_name, command_params}, _update_param{update_param} {}

void UpdateCommand::execute() {
    auto &records = record_storage.get_records(table_name);
    for (auto &record: records) {
        if (std::all_of(command_params.begin(), command_params.end(), [&record](const auto &command_param) {
            return record->match(command_param);
        })) {
            record->update(_update_param);
        }
    }
    std::cout << "All rows from table `" << table_name << "` "
              << "updated: " << _update_param.name << " "
              << _update_param.value << std::endl;
}

