#pragma once

#include <regex>
#include "Command.h"

class UpdateCommand : public Command {
public:
    UpdateCommand(const RecordStorage &record_storage, const std::string &table_name,
                  const std::vector<cmd::CommandParam> &command_params);

    void execute() override;

    static const std::string COMMAND_REGEX_CONDITION;
};
