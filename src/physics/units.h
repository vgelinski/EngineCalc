#ifndef UNITS_H
#define UNITS_H

#include <cstdio>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "../common/types.h"

namespace engc::physics {

enum class SimpleUnitType {
    Length, Mass, Time, Temperature, Angle,
};

class SimpleUnitValues;

class SimpleUnit {
private:

    friend class SimpleUnitValues;

    static SimpleUnit * constructorWrapper(
            const long double& multiplier,
            const SimpleUnitType type,
            const std::string& name,
            std::vector<const SimpleUnit *>& vals
    );

    SimpleUnit(
            const long double& multiplier,
            const SimpleUnitType type,
            const std::string& name,
            std::vector<const SimpleUnit *>& vals
    );

public:

    const long double multiplier;
    const SimpleUnitType type;
    const std::string name;

    virtual ~SimpleUnit();

    virtual const SimpleUnit * const siUnit() const;
    virtual std::string toString() const;
};

class SimpleUnitValues {
private:

    SimpleUnitValues();

    std::vector<const SimpleUnit *> vals;
public:

     const SimpleUnit * const HundredthMilliMeters;
     const SimpleUnit * const MilliMeters;
     const SimpleUnit * const Meters;
     const SimpleUnit * const KiloMeters;

     const SimpleUnit * const Grams;
     const SimpleUnit * const Kilograms;

     const SimpleUnit * const MilliSeconds;
     const SimpleUnit * const Seconds;
     const SimpleUnit * const Minutes;
     const SimpleUnit * const Hours;

     const SimpleUnit * const Kelvins;

     const SimpleUnit * const Radians;
     const SimpleUnit * const Degrees;
     const SimpleUnit * const Rounds;

    static const SimpleUnitValues * Get();

    static const std::vector<SimpleUnit const *>& values();
};

class CompoundUnit {
private:
    std::unordered_map<SimpleUnit const *, long double> units;
    const long double multiplier;
    const uname_t name;

    CompoundUnit(
            const std::unordered_map<SimpleUnit const *, long double>& units,
            const long double& multiplier = 1.0L,
            const uname_t& name = {}
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
    virtual bool canBeConverted(const std::shared_ptr<CompoundUnit>& o) const;
    virtual std::shared_ptr<CompoundUnit> withName(
            const std::string& name,
            const long double& multiplier = 1.0L
     ) const;

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
