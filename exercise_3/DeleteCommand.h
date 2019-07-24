#pragma once


#include "Command.h"

class DeleteCommand : public Command {
public:
    DeleteCommand(const RecordStorage &record_storage, const std::string &table_name,
                  const std::vector<cmd::CommandParam> &command_params);

    void execute() override;

    static const std::string COMMAND_REGEX_CONDITION;
};
