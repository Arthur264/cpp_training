#pragma once


#include "Command.h"

class DeleteCommand : public Command {
public:
    static const std::string COMMAND_REGEX_CONDITION;

    DeleteCommand(RecordStorage &record_storage, const std::string &table_name,
                  const std::vector<record::CompareParam> &command_params);

    void execute() override;
};
