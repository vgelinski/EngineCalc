#include "value.h"

#include "../util/exceptions/illegal_argument_exception.h"

using namespace std;
using namespace engc::math;
using namespace engc::physics;
using namespace engc::util;

Value::Value(const fret_t& value, const shared_ptr<CompoundUnit> unit):
        value(value), unit(unit) {}

Value::~Value(){}

shared_ptr<Value> Value::convertTo(const shared_ptr<CompoundUnit>& u) const {
    if (!unit->canBeConverted(u))
        throw IllegalArgumentException(
                unit->toDebugString() + 
                " Cannot be converted to " + 
                u->toDebugString()
        );

    auto val = value * unit->siMultiplier() / u->siMultiplier();
    return make_shared<Value>(val, u);
}

shared_ptr<Value> Value::convertToSi() const {
    auto val = value * unit->siMultiplier();
    return make_shared<Value>(val, unit->siUnit());
}

