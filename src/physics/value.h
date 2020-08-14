#ifndef VALUE_H
#define VALUE_H

#include <memory>

#include "../math/function/function.h"
#include "units.h"

namespace engc::physics {

class Value {
public:
    const math::fret_t value;
    const std::shared_ptr<CompoundUnit> unit;

    Value(const math::fret_t& value, const std::shared_ptr<CompoundUnit> unit);
    virtual ~Value();

    std::shared_ptr<Value> convertTo(const std::shared_ptr<CompoundUnit>& unit) const;
    std::shared_ptr<Value> convertToSi() const;
    std::string toString() const;
};

}; //end namespace

#endif
