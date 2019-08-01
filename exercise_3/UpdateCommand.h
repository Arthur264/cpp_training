#pragma once

#include <regex>
#include "Command.h"

class UpdateCommand : public Command {
public:
    UpdateCommand(RecordStorage &record_storage, const std::string &table_name,
                  const std::vector<record::CompareParam> &command_params,
                  const record::CompareParam &update_param);

    void execute() override;

    static const std::string COMMAND_REGEX_CONDITION;
private:
    const record::CompareParam _update_param;
};
