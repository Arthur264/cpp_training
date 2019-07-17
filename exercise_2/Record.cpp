#include <sstream>
#include "Record.h"

Record::Record(int id) : _id(id) {}

int Record::get_id() const {
    return _id;
}
