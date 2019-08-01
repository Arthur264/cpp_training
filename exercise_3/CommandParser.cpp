#include <sstream>
#include <algorithm>
#include <regex>
#include "CommandParser.h"

namespace cmd {
    const std::string WHITESPACE = " ";

    inline std::string ltrim(const std::string &s) {
        return std::regex_replace(s, std::regex("^\\s+"), std::string(""));
    }

    inline std::string rtrim(const std::string &s) {
        return std::regex_replace(s, std::regex("\\s+$"), std::string(""));
    }

    inline std::string trim(const std::string &s) {
        return ltrim(rtrim(s));
    }

    inline std::vector<std::string> split(const std::string &str, const std::string &delimiter) {
        if (str.find(delimiter) == std::string::npos) {
            return std::vector<std::string>{str};
        }

        std::size_t pos_start = 0, pos_end;
        const int delimiter_len = delimiter.length();
        std::vector<std::string> result;

        while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos) {
            result.push_back(str.substr(pos_start, pos_end - pos_start));
            pos_start = pos_end + delimiter_len;
        }

        result.push_back(str.substr(pos_start));
        return result;
    }
}

std::vector<record::CompareParam> CommandParser::parse_expression(const std::string &expression) const {
    const std::string delimiter = "&&";
    const auto conditions = cmd::split(expression, delimiter);
    std::vector<record::CompareParam> vector_command_params{};

    for (const auto &it: conditions) {
        vector_command_params.push_back(CommandParser::parse_condition(it));
    }
    return vector_command_params;
}


record::CompareParam CommandParser::parse_condition(const std::string &condition) const {
    auto trim_condition = cmd::trim(condition);
    auto vector_params = cmd::split(trim_condition, cmd::WHITESPACE);

    if (vector_params.size() != 3) {
        throw std::invalid_argument("Wrong number of argument");
    }

    const auto &name = vector_params[0];
    const auto &value = vector_params[2];
    const auto &comparison_sign = vector_params[1];

    auto comparison = Command::comparisons_map.find(comparison_sign);
    if (Command::comparisons_map.end() == comparison) {
        throw std::invalid_argument("Invalid comparison expression");
    }
    const auto comparison_func = comparison->second;

    return record::CompareParam{name, value, comparison_func, comparison_sign};
}

record::CompareParam CommandParser::parse_update_param(const std::string &expression) const {
    auto trim_condition = cmd::trim(expression);
    auto vector_params = cmd::split(trim_condition, cmd::WHITESPACE);

    if (vector_params.size() != 2) {
        throw std::invalid_argument("Wrong number of argument");
    }

    const auto &name = vector_params[0];
    const auto &value = vector_params[1];

    return record::CompareParam{name, value, std::equal_to<>(), "="};
}