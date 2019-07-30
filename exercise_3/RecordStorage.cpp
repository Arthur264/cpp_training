#include <iostream>
#include <algorithm>
#include "RecordStorage.h"


RecordStorage::RecordStorage(record::StorageMap storage_map) : _storage_map{std::move(storage_map)} {}


void RecordStorage::_sort(const std::string &table_name) {
    auto compare_records_id = [](const std::shared_ptr<Record> &first_record,
                                 const std::shared_ptr<Record> &second_record) -> bool {
        return first_record->get_id() < second_record->get_id();
    };
    std::sort(_record_map[table_name].begin(), _record_map[table_name].end(), compare_records_id);
}

void RecordStorage::_write_in_file(const std::string &outfile_path, const record::RecordVectorPtr &records) const {
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
    for (const auto &path: _storage_map) {
        auto table_name = path.second.second;
        auto out_file = path.second.first;
        _sort(table_name);
        _write_in_file(out_file, _record_map[table_name]);
    }
}

void RecordStorage::add(char record_type, const std::shared_ptr<Record> &record_ptr) {
    auto table_name = _storage_map.find(record_type)->second.second;
    _record_map[table_name].push_back(record_ptr);
}

record::RecordVectorPtr &RecordStorage::get_records(const std::string &table_name) {
    auto it = _record_map.find(table_name);
    std::cout << table_name << std::endl;
    if (_record_map.end() == it) {
        throw std::invalid_argument("Table not found");
    }
    return it->second;
}

record::RecordMap &RecordStorage::get_record_map() {
    return _record_map;
}