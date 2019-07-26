#pragma once

#include <string>
#include <vector>
#include "Command.h"

namespace cmd {
    inline std::string trim(const std::string &str);

    inline std::vector<std::string> split(const std::string &str, const std::string &delimiter);
}

class CommandParser {
public:
    record::CompareParam parse_condition(std::string &condition) const;

    std::vector<record::CompareParam> parse_expression(std::string &expression) const;

    record::CompareParam parse_update_param(std::string &expression) const;
};