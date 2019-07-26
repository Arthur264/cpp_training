#pragma once

#include <functional>
#include "RecordStorage.h"

namespace cmd {
    using ComparisonsMap = std::map<std::string, record::ComparisonFunc>;
}

class Command {
public:
    Command(RecordStorage &record_storage, std::string table_name,
            std::vector<record::CompareParam> command_params);

    static const cmd::ComparisonsMap comparisons_map;

    virtual ~Command() = default;

    virtual void execute() = 0;

protected:
    RecordStorage &record_storage;
    const std::string table_name;
    const std::vector<record::CompareParam> command_params;


};