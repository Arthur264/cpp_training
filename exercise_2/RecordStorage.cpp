#include <fstream>
#include <iostream>
#include <algorithm>
#include <thread>
#include "RecordStorage.h"


RecordStorage::RecordStorage(FilePathMap file_path_map) : _file_path_map{std::move(file_path_map)} {}


void RecordStorage::_sort(char record_type) {
    std::cout << "Sort " << record_type << " records in RecordStorage" << std::endl;
    auto sort_record = [](const std::shared_ptr<IRecord> first_record,
                          const std::shared_ptr<IRecord> second_record) -> bool {
        return first_record->get_id() < second_record->get_id();
    };
    std::sort(_record_map[record_type].begin(), _record_map[record_type].end(), sort_record);
}

void RecordStorage::_write_in_file(const std::string &outfile_path, const RecordVectorPtr &records) const {
    std::ofstream out_file(outfile_path);
    if (!out_file.is_open()) {
        std::cerr << "File not open" << std::endl;
        exit(EXIT_FAILURE);
    }
    for (const auto &record: records) {
        out_file << record->get_formatted();
    }
}

void RecordStorage::dumps() {
    for (const auto &path: _file_path_map) {
        auto record_type = path.first;
        auto out_file = path.second;
        _sort(record_type);
        _write_in_file(out_file, _record_map[record_type]);
    }
}


void RecordStorage::add(char record_type, const std::shared_ptr<IRecord> &record_ptr) {
    _record_map[record_type].push_back(record_ptr);
}