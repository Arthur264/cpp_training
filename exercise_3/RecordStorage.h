#pragma once

#include <memory>
#include <map>
#include "Record.h"

namespace record {
    using StorageMap = std::map<char, std::pair<std::string, std::string>>;
}


class RecordStorage {
public:
    explicit RecordStorage(record::StorageMap storage_map);

    void dumps();

    void add(char record_type, const std::shared_ptr<Record> &record_ptr);

    record::RecordVectorPtr &get_records(const std::string &table_name);

    record::RecordMap &get_record_map();

    ~RecordStorage() = default;

private:
    record::RecordMap _record_map;
    const record::StorageMap _storage_map;

    void _write_in_file(const std::string &outfile_path, const record::RecordVectorPtr &records) const;

    void _sort(const std::string &record_type);

};

