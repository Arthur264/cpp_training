#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Record {
public:
    Record(int id);

    int get_id() const;

    virtual std::string get_formatted() const = 0;

    virtual ~Record() = default;

protected:
    const int _id;
};


namespace record {
    using FilePathMap = std::unordered_map<char, std::string>;
    using RecordVectorPtr = std::vector<std::shared_ptr<Record>>;
    using RecordMap = std::unordered_map<char, RecordVectorPtr>;
}