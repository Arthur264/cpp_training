#include "UpdateCommand.h"

const std::string UpdateCommand::COMMAND_REGEX_CONDITION("UPDATE (.+) WHERE (.+);");

UpdateCommand::UpdateCommand(const RecordStorage &record_storage, const std::string &table_name,
                             const std::vector<cmd::CommandParam> &command_params) :
        Command(record_storage, table_name, command_params) {}

void UpdateCommand::execute() {}

