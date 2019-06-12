#ifndef UNITS_H
#define UNITS_H

#include <cstdio>
#include <optional>
#include <string>
#include <unordered_map>

namespace engc::physics {

enum class SimpleUnitType {
    Length, Mass, Time, Temperature,
};

class SimpleUnit {
private:
    const SimpleUnitType &type;
    const std::string unit;

    SimpleUnit(const SimpleUnitType &type, const std::string &unit);

public:

    static const SimpleUnit * const Meters;
    static const SimpleUnit * const Kilograms;
    static const SimpleUnit * const Seconds;
    static const SimpleUnit * const Kelvins;

    virtual ~SimpleUnit();

    virtual std::string toString() const;
};

class MultipleUnit {
private:
    const long double multiplier;
    const SimpleUnit * const unit;
    const std::string name;

    MultipleUnit(
            const long double &multiplier,
            const SimpleUnit * const unit,
            const std::string &name
    );

public:
    virtual ~MultipleUnit();

    virtual std::string toString() const;
};

class CompoundUnit {
private:
    std::unordered_map<MultipleUnit const *, long double> units;
    const std::optional<std::string> name;

public:
    virtual ~CompoundUnit();
    virtual std::string toString() const;
    virtual std::string toDebugString() const;
    virtual std::string toLatexString() const;
};
}; //end namespace
#endif
