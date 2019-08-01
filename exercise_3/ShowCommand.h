#pragma once

#include <regex>
#include "Command.h"
#include "Invoker.h"

class ShowCommand : public Command {
public:
    ShowCommand(RecordStorage &record_storage, const std::string &table_name,
                const std::vector<record::CompareParam> &command_params = std::vector<record::CompareParam>());

    void execute() override;

    static const std::string COMMAND_REGEX;
    static const std::string COMMAND_REGEX_CONDITION;
private:
    bool _print_table(const std::string &table_name);

    record::RecordVectorPtr _filter_records(const record::RecordVectorPtr &records) const;
};

