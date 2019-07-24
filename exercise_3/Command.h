#pragma once

#include <functional>
#include "RecordStorage.h"

namespace cmd {
    using ComparisonsMap = std::map<std::string, std::function<bool(int, int)>>;

    struct CommandParam {
        std::string name;
        int value;
        std::string comparison;
    };
}

class Command {
public:
    Command(const RecordStorage &record_storage, std::string table_name, std::vector<cmd::CommandParam> command_params);

    static const cmd::ComparisonsMap comparisons_map;

    virtual ~Command() = default;

    virtual void execute() = 0;

protected:
    const RecordStorage record_storage;
    const std::string table_name;
    const std::vector<cmd::CommandParam> command_params;
};