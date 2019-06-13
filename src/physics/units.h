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

#ifndef OLGGCC
typedef std::optional<std::string> uname_t;
#else
typedef std::experimental::optional<std::string> uname_t;
#endif

enum class SimpleUnitType {
    Length, Mass, Time, Temperature, Angle,
};

class MultipleUnit {
private:
    static std::vector<const MultipleUnit *> vals;

    MultipleUnit(
            const long double &multiplier,
            const SimpleUnitType type,
            const std::string &name
    );

public:

    static const MultipleUnit * const HundredthMilliMeters;
    static const MultipleUnit * const MilliMeters;
    static const MultipleUnit * const Meters;
    static const MultipleUnit * const KiloMeters;

    static const MultipleUnit * const Grams;
    static const MultipleUnit * const Kilograms;

    static const MultipleUnit * const MilliSeconds;
    static const MultipleUnit * const Seconds;
    static const MultipleUnit * const Minutes;
    static const MultipleUnit * const Hours;

    static const MultipleUnit * const Kelvins;

    static const MultipleUnit * const Radians;
    static const MultipleUnit * const Degrees;

    const long double multiplier;
    const SimpleUnitType type;
    const std::string name;

    static const std::vector<MultipleUnit const *>& values();

    virtual ~MultipleUnit();

    virtual std::string toString() const;
};

class CompoundUnit {
private:
    std::unordered_map<MultipleUnit const *, long double> units;
    const uname_t name;

    CompoundUnit(
            const std::unordered_map<MultipleUnit const *, long double> &units,
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
    CompoundUnit(const MultipleUnit * const unit);
    virtual ~CompoundUnit();
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
