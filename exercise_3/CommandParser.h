#pragma once

#include <string>
#include <vector>
#include "Command.h"

namespace cmd {
    inline std::string ltrim(const std::string &s);

    inline std::string rtrim(const std::string &s);

    inline std::string trim(const std::string &s);

    inline std::vector<std::string> split(const std::string &str, const std::string &delimiter);
}

class CommandParser {
public:
    record::CompareParam parse_condition(const std::string &condition) const;

    std::vector<record::CompareParam> parse_expression(const std::string &expression) const;

    record::CompareParam parse_update_param(const std::string &expression) const;
};