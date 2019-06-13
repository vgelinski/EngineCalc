#include "units.h"

#include <cmath>

using namespace engc::physics;
using namespace std;

#define SUT SimpleUnitType
#define MU  MultipleUnit

vector<MU const *> MU::vals;

const MU * const MU::HundredthMilliMeters = new MU(0.01L * 0.001L, SUT::Length, "mm/100");
const MU * const MU::MilliMeters = new MU(0.001L, SUT::Length, "mm");
const MU * const MU::Meters = new MU(1.0L, SUT::Length, "m");
const MU * const MU::KiloMeters = new MU(1000.0L, SUT::Length, "km");

const MU * const MU::Grams = new MU(0.001L, SUT::Mass, "g");
const MU * const MU::Kilograms = new MU(1.0L, SUT::Mass, "kg");

const MU * const MU::MilliSeconds = new MU(0.001L, SUT::Time, "ms");
const MU * const MU::Seconds = new MU(1.0L, SUT::Time, "s");
const MU * const MU::Minutes = new MU(60.0L, SUT::Time, "min");
const MU * const MU::Hours = new MU(60.0L * 60.0L, SUT::Time, "h");

  const MU * const MU::Kelvins = new MU(1.0L, SUT::Temperature, "K°");

const MU * const MU::Radians = new MU(1.0L, SUT::Angle , "rad");
const MU * const MU::Degrees = new MU(2.0L * M_PI/ 360.0L, SUT::Angle , "deg");

