#include "DeleteCommand.h"

const std::string DeleteCommand::COMMAND_REGEX_CONDITION = "DELETE (.+) WHERE (.+);";

DeleteCommand::DeleteCommand(const RecordStorage &record_storage, const std::string &table_name,
                             const std::vector<cmd::CommandParam> &command_params) :
        Command(record_storage, table_name, command_params) {}

void DeleteCommand::execute() {}

