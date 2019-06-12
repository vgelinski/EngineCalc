#include "units.h"

using namespace engc::physics;
using namespace std;

SimpleUnit::SimpleUnit(const SimpleUnitType &type, const string &unit)
        : type(type), unit(unit) {}

SimpleUnit::~SimpleUnit() {}

string SimpleUnit::toString() const {return unit;}

MultipleUnit::MultipleUnit(
        const long double &multiplier,
        const SimpleUnit * const unit,
        const string &name)
        : multiplier(multiplier), unit(unit), name(name) {}

MultipleUnit::~MultipleUnit() {}

string MultipleUnit::toString() const {return name;}

CompoundUnit::~CompoundUnit() {}

string CompoundUnit::toString() const {
    return name.value_or(toDebugString());
}

string CompoundUnit::toDebugString() const {return "";}

string CompoundUnit::toLatexString() const {return "";}

