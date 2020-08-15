#include "units.h"

#include <cmath>

using namespace engc::physics;
using namespace std;

#define SUT SimpleUnitType
#define SU  SimpleUnit
#define SUV  SimpleUnitValues

const SUV * SUV::Get() {
    static auto instance = new SUV();
    return instance;
}

SUV::SUV() :
    vals(),

    HundredthMilliMeters(SU::constructorWrapper(0.01L * 0.001L, SUT::Length, "mm/100", vals)),
    MilliMeters(SU::constructorWrapper(0.001L, SUT::Length, "mm", vals)),
    Meters(SU::constructorWrapper(1.0L, SUT::Length, "m", vals)),
    KiloMeters(SU::constructorWrapper(1000.0L, SUT::Length, "km", vals)),

    Grams(SU::constructorWrapper(0.001L, SUT::Mass, "g", vals)),
    Kilograms(SU::constructorWrapper(1.0L, SUT::Mass, "kg", vals)),

    MilliSeconds(SU::constructorWrapper(0.001L, SUT::Time, "ms", vals)),
    Seconds(SU::constructorWrapper(1.0L, SUT::Time, "s", vals)),
    Minutes(SU::constructorWrapper(60.0L, SUT::Time, "min", vals)),
    Hours(SU::constructorWrapper(60.0L * 60.0L, SUT::Time, "h", vals)),

    Kelvins(SU::constructorWrapper(1.0L, SUT::Temperature, "K°", vals)),

    Radians(SU::constructorWrapper(1.0L, SUT::Angle , "rad", vals)),
    Degrees(SU::constructorWrapper(2.0L * M_PI/ 360.0L, SUT::Angle , "deg", vals)),
    Rounds(SU::constructorWrapper(2.0L * M_PI, SUT::Angle , "r", vals)) {}

