#pragma once

#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <memory>
#include <functional>
#include <unordered_map>

namespace record {
    using ComparisonFunc = std::function<bool(int, int)>;
    using PropMap = std::unordered_map<std::string, int*>;
    struct CompareParam {
        std::string name;
        std::string value;
        ComparisonFunc comparison;
        std::string comparison_sign;
    };
}

class Record {
public:
    Record(int id);

    int get_id() const;

    virtual std::string get_formatted() const = 0;

    virtual std::string get_pretty_printed() const = 0;

    virtual bool match(const record::CompareParam &compare_param) const = 0;

    virtual void update(const record::CompareParam &compare_param) = 0;

    virtual ~Record() = default;

protected:
    const int _id;

    virtual record::PropMap get_int_props() = 0;

    bool match_int(const record::CompareParam &compare_param) const;

    void update_int(const record::CompareParam &compare_param);

    void validation_update(const std::string &name) const;

    void validation_string(const record::CompareParam &compare_param) const;
};


namespace record {
    using RecordVectorPtr = std::vector<std::shared_ptr<Record>>;
    using RecordMap = std::unordered_map<std::string, RecordVectorPtr>;

    template<class T>
    T parse_parameter(std::stringstream &stream) {
        T buffer;
        std::string tmp;
        if (!std::getline(stream, tmp, ',')) {
            std::cerr << "Parse args failure" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::stringstream ss(tmp);
        ss >> buffer;
        return buffer;
    }

}