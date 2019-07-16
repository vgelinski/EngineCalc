#ifndef UNITS_H
#define UNITS_H

#include <cstdio>
#include <memory>

#ifndef OLDGCC
#include <optional>
#else
#include <experimental/optional>
#endif

#include <string>
#include <unordered_map>
#include <vector>

namespace engc::physics {

typedef std::optional<std::string> uname_t;

enum class SimpleUnitType {
    Length, Mass, Time, Temperature, Angle,
};

class SimpleUnit {
private:
    static std::vector<const SimpleUnit *> vals;

    SimpleUnit(
            const long double &multiplier,
            const SimpleUnitType type,
            const std::string &name
    );

public:

    static const SimpleUnit * const HundredthMilliMeters;
    static const SimpleUnit * const MilliMeters;
    static const SimpleUnit * const Meters;
    static const SimpleUnit * const KiloMeters;

    static const SimpleUnit * const Grams;
    static const SimpleUnit * const Kilograms;

    static const SimpleUnit * const MilliSeconds;
    static const SimpleUnit * const Seconds;
    static const SimpleUnit * const Minutes;
    static const SimpleUnit * const Hours;

    static const SimpleUnit * const Kelvins;

    static const SimpleUnit * const Radians;
    static const SimpleUnit * const Degrees;

    const long double multiplier;
    const SimpleUnitType type;
    const std::string name;

    static const std::vector<SimpleUnit const *>& values();

    virtual ~SimpleUnit();

    virtual const SimpleUnit * const siUnit() const;
    virtual std::string toString() const;
};

class CompoundUnit {
private:
    std::unordered_map<SimpleUnit const *, long double> units;
    const uname_t name;

    CompoundUnit(
            const std::unordered_map<SimpleUnit const *, long double> &units,
            const uname_t &name = {}
    );


    friend std::shared_ptr<CompoundUnit> operator*(
            const std::shared_ptr<CompoundUnit> lhs,
            const std::shared_ptr<CompoundUnit> rhs
    );

    friend std::shared_ptr<CompoundUnit> operator/(
            const std::shared_ptr<CompoundUnit> lhs,
            const std::shared_ptr<CompoundUnit> rhs
    );

public:
    CompoundUnit(const SimpleUnit * const unit);
    virtual ~CompoundUnit();

    virtual long double siMultiplier() const;
    virtual std::shared_ptr<CompoundUnit> siUnit() const;

    virtual std::string toString() const;
    virtual std::string toDebugString() const;
    virtual std::string toLatexString() const;
};

std::shared_ptr<CompoundUnit> operator*(
        const std::shared_ptr<CompoundUnit> lhs,
        const std::shared_ptr<CompoundUnit> rhs
);

std::shared_ptr<CompoundUnit> operator/(
        const std::shared_ptr<CompoundUnit> lhs,
        const std::shared_ptr<CompoundUnit> rhs
);
}; //end namespace
#endif
