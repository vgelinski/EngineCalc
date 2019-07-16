#include "value.h"

using namespace std;
using namespace engc::physics;

Value::Value(const long double& value, const shared_ptr<CompoundUnit> unit):
        value(value), unit(unit) {}

Value::~Value(){}

shared_ptr<Value> Value::convertTo(const shared_ptr<CompoundUnit>& u) const {
    auto val = value * unit->siMultiplier() / u->siMultiplier();
    return make_shared<Value>(val, u);
}

shared_ptr<Value> Value::convertToSi() const {
    auto val = value * unit->siMultiplier();
    return make_shared<Value>(val, unit->siUnit());
}

