#ifndef UNITS_H
#define UNITS_H

#include <string>

namespace engc::physics {

enum class SimpleUnitType {
    Length, Mass, Time, Temperature,
};

class SimpleUnit {
private:
    const SimpleUnitType &type;
    const std::string unit;

    SimpleUnit(const SimpleUnitType type, const std::string &unit);

public:
    virtual ~SimpleUnit();

    virtual std::string toString() const;
};

class MultipleUnit {
private:
    const long double multiplier;
    const SimpleUnit &unit;
    const std::string name;

    MultipleUnit(
            const long double &multiplier,
            const SimpleUnit &unit,
            const std::string &name
    );

public:
    virtual ~MultipleUnit();

    virtual std::string toString() const;
};
}; //end namespace
#endif
