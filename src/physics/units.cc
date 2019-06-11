#include "units.h"

using namespace engc::physics;
using namespace std;

SimpleUnit::SimpleUnit(const SimpleUnitType type, const string &unit):
        type(type), unit(unit) {}

SimpleUnit::~SimpleUnit() {}

string SimpleUnit::toString() const {return unit;}
