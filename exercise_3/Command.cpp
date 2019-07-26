#include "Command.h"

const cmd::ComparisonsMap Command::comparisons_map = {
        {"<",  std::less<>()},
        {">",  std::greater<>()},
        {"=",  std::equal_to<>()},
        {"<=", std::less_equal<>()},
        {">=", std::greater_equal<>()},
};

Command::Command(RecordStorage &record_storage, std::string table_name,
                 std::vector<record::CompareParam> command_params) :
        record_storage{record_storage},
        table_name{std::move(table_name)},
        command_params{std::move(command_params)} {
}