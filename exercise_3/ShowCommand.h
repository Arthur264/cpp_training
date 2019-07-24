#pragma once

#include <regex>
#include "Command.h"
#include "Invoker.h"

class ShowCommand : public Command {
public:
    ShowCommand(const RecordStorage &record_storage, const std::string &table_name,
                const std::vector<cmd::CommandParam> &command_params);

    void execute() override;

    static const std::string COMMAND_REGEX;
    static const std::string COMMAND_REGEX_CONDITION;
private:
    bool _print_table(const std::string &table_name, const record::RecordMap &record_map) const;

    record::RecordVectorPtr _filter_records(record::RecordVectorPtr records) const;
};

