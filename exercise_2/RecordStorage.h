#pragma once

#include <memory>
#include "Record.h"


class RecordStorage {
public:
    explicit RecordStorage(record::FilePathMap file_path_map);

    void dumps();

    void add(char record_type, const std::shared_ptr<Record> &record_ptr);


    ~RecordStorage() = default;

private:
    record::RecordMap _record_map;
    const record::FilePathMap _file_path_map;

    void _write_in_file(const std::string &outfile_path, const record::RecordVectorPtr &records) const;

    void _sort(char record_type);

};

