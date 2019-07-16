#pragma once

#include <string>

class IRecord {
public:
    virtual int get_id() const = 0;

    virtual std::string get_formatted() const = 0;

    virtual ~IRecord() = default;
};
 