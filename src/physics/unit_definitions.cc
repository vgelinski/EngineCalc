#include "units.h"

#include <cmath>

using namespace engc::physics;
using namespace std;

#define SUT SimpleUnitType
#define SU  SimpleUnit

vector<SU const *> SU::vals;

const SU * const SU::HundredthMilliMeters = new SU(0.01L * 0.001L, SUT::Length, "mm/100");
const SU * const SU::MilliMeters = new SU(0.001L, SUT::Length, "mm");
const SU * const SU::Meters = new SU(1.0L, SUT::Length, "m");
const SU * const SU::KiloMeters = new SU(1000.0L, SUT::Length, "km");

const SU * const SU::Grams = new SU(0.001L, SUT::Mass, "g");
const SU * const SU::Kilograms = new SU(1.0L, SUT::Mass, "kg");

const SU * const SU::MilliSeconds = new SU(0.001L, SUT::Time, "ms");
const SU * const SU::Seconds = new SU(1.0L, SUT::Time, "s");
const SU * const SU::Minutes = new SU(60.0L, SUT::Time, "min");
const SU * const SU::Hours = new SU(60.0L * 60.0L, SUT::Time, "h");

const SU * const SU::Kelvins = new SU(1.0L, SUT::Temperature, "K°");

const SU * const SU::Radians = new SU(1.0L, SUT::Angle , "rad");
const SU * const SU::Degrees = new SU(2.0L * M_PI/ 360.0L, SUT::Angle , "deg");
const SU * const SU::Rounds = new SU(2.0L * M_PI, SUT::Angle , "r");

