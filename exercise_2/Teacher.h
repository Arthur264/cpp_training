#pragma once

#include <string>
#include "IPerson.h"
#include "IRecord.h"

class Teacher : public IPerson, public IRecord {
public:
    static constexpr const char RECORD_PREFIX = 'T';

    Teacher(int id, std::string name);

    std::string get_name() const override;

    int get_id() const override;

    std::string get_formatted() const override;

private:
    const int _id;
    const std::string _name;
};