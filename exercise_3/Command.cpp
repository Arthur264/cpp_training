#include "Command.h"

const cmd::ComparisonsMap Command::comparisons_map = {
        {"<",  std::less<>()},
        {">",  std::greater<>()},
        {"=",  std::equal_to<>()},
        {"<=", std::less_equal<>()},
        {">=", std::greater_equal<>()},
};

Command::Command(RecordStorage &record_storage, const std::string &table_name,
                 const std::vector<record::CompareParam> &command_params) :
        record_storage{record_storage},
        table_name{table_name},
        command_params{command_params} {
}