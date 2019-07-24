#include <stdexcept>
#include "CommandParser.h"
#include "Command.h"

namespace cmd {
    inline std::string trim(std::string &str) {
        std::size_t first = str.find_first_not_of(' ');
        if (std::string::npos == first) {
            return str;
        }
        std::size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    inline std::vector<std::string> split(std::string &str, const std::string &delimiter) {
        if (str.find(delimiter) == std::string::npos) {
            return std::vector<std::string>{str};
        }
        std::size_t pos = 0;
        std::vector<std::string> result;

        do {
            pos = str.find(delimiter);
            result.push_back(str.substr(0, pos));
            str.erase(0, pos + delimiter.length());
        } while (pos != std::string::npos);

        return result;
    }
}

std::vector<cmd::CommandParam> CommandParser::parse_expression(std::string expression) const {
    std::vector<cmd::CommandParam> vector_command_params{};
    const std::string delimiter = "&&";
    auto conditions = cmd::split(expression, delimiter);

    for (auto it: conditions) {
        vector_command_params.push_back(CommandParser::parse_condition(it));
    }
    return vector_command_params;
}


cmd::CommandParam CommandParser::parse_condition(std::string &condition) const {
    auto trim_condition = cmd::trim(condition);
    std::vector<std::string> vector_params = cmd::split(trim_condition, " ");

    if (vector_params.size() != 3) {
        throw std::invalid_argument("Wrong argument");
    }

    auto name = vector_params[0];
    auto value = std::stoi(vector_params[2]);
    auto comparison = vector_params[1];
    return cmd::CommandParam{name, value, comparison};
}