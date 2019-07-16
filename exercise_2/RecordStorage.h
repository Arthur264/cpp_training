#pragma once

#include <string>
#include <vector>
#include <map>
#include <memory>
#include "IRecord.h"

using FilePathMap = std::map<char, std::string>;
using RecordVectorPtr = std::vector<std::shared_ptr<IRecord>>;
using RecordMap = std::map<char, RecordVectorPtr>;

class RecordStorage {
public:
    RecordStorage(FilePathMap file_path_map);

    void dumps();

    void add(char record_type, const std::shared_ptr<IRecord> &record_ptr);


    ~RecordStorage() = default;

private:
    RecordMap _record_map;
    const FilePathMap _file_path_map;

    void _write_in_file(const std::string &outfile_path, const RecordVectorPtr &records) const;

    void _sort(char record_type);

};

