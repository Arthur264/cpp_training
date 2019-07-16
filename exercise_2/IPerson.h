#pragma once

#include <string>

class IPerson {
public:
    virtual std::string get_name() const = 0;

    virtual ~IPerson() = default;
};