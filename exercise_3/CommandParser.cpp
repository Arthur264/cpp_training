#include <stdexcept>
#include <iterator>
#include "CommandParser.h"

namespace cmd {
    inline std::string trim(const std::string &str) {
        if(str == " "){
            return "";
        }
        std::size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) {
            return str;
        }
        std::size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    inline std::vector<std::string> split(const std::string &str, const std::string &delimiter) {
        if (str.find(delimiter) == std::string::npos) {
            return std::vector<std::string>{str};
        }

        std::size_t pos_start = 0, pos_end;
        int delimiter_len = delimiter.length();
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
    std::vector<record::CompareParam> vector_command_params{};
    const std::string delimiter = "&&";
    auto conditions = cmd::split(expression, delimiter);

    for (const auto &it: conditions) {
        vector_command_params.push_back(CommandParser::parse_condition(it));
    }
    return vector_command_params;
}


record::CompareParam CommandParser::parse_condition(const std::string &condition) const {
    auto trim_condition = cmd::trim(condition);
    std::vector<std::string> vector_params = cmd::split(trim_condition, " ");

    if (vector_params.size() != 3) {
        throw std::invalid_argument("Wrong number of argument");
    }

    auto name = vector_params[0];
    auto value = vector_params[2];
    auto comparison_sing = vector_params[1];

    auto comparison = Command::comparisons_map.find(comparison_sing);
    if (Command::comparisons_map.end() == comparison) {
        throw std::invalid_argument("Invalid comparison expression");
    }
    auto comparison_func = comparison->second;

    return record::CompareParam{name, value, comparison_func, comparison_sing};
}

record::CompareParam CommandParser::parse_update_param(const std::string &expression) const {
    auto trim_condition = cmd::trim(expression);
    std::vector<std::string> vector_params = cmd::split(trim_condition, " ");

    if (vector_params.size() != 2) {
        throw std::invalid_argument("Wrong number of argument");
    }

    auto name = vector_params[0];
    auto value = vector_params[1];

    return record::CompareParam{name, value, std::equal_to<>(), "="};
}