#pragma once


#include <string>
#include <vector>
#include "Command.h"

namespace cmd {
    inline std::string trim(std::string &str);

    inline std::vector<std::string> split(std::string &str, const std::string &delimiter);
}

class CommandParser {
public:
    cmd::CommandParam parse_condition(std::string &condition) const;

    std::vector<cmd::CommandParam> parse_expression(std::string expression) const;
};