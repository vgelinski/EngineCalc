#ifndef VALUE_H
#define VALUE_H

#include <memory>

#include "units.h"

namespace engc::physics {

class Value {
public:
    const long double value;
    const std::shared_ptr<CompoundUnit> unit;

    Value(const long double &value, const std::shared_ptr<CompoundUnit> unit);
    virtual ~Value();

    std::shared_ptr<Value> convertTo(const std::shared_ptr<CompoundUnit> &unit);
    std::shared_ptr<Value> convertToSi();
    std::string toString() const;
};

}; //end namespace

#endif
