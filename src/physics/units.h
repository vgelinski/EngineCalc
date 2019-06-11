#ifndef UNITS_H
#define UNITS_H

#include <string>

namespace engc::physics {

enum class SimpleUnitType {
    Length, Mass, Time, Temperature,
};

class SimpleUnit {
private:
    const SimpleUnitType type;
    const std::string unit;

    SimpleUnit(const SimpleUnitType type, const std::string &unit);

public:
    virtual ~SimpleUnit();

    virtual std::string toString() const;
};
}; //end namespace
#endif
