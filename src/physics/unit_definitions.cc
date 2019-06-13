#include "units.h"

#include <cmath>

using namespace engc::physics;
using namespace std;

#define SUT SimpleUnitType
#define SU  SimpleUnit
#define MU  MultipleUnit

vector<MU const *> MU::vals;

const SU * const SU::Meters = new SU(SUT::Length, "m");
const SU * const SU::Kilograms = new SU(SUT::Mass, "kg");
const SU * const SU::Seconds = new SU(SUT::Time, "s");
const SU * const SU::Kelvins = new SU(SUT::Temperature, "K°");
const SU * const SU::Radians = new SU(SUT::Angle, "rad");

const MU * const MU::HundredthMilliMeters = new MU(0.01L * 0.001L, SU::Meters, "mm/100");
const MU * const MU::MilliMeters = new MU(0.001L, SU::Meters, "mm");
const MU * const MU::Meters = new MU(1.0L, SU::Meters, "m");
const MU * const MU::KiloMeters = new MU(1000.0L, SU::Meters, "km");

const MU * const MU::Grams = new MU(0.001L, SU::Kilograms, "g");
const MU * const MU::Kilograms = new MU(1.0L, SU::Kilograms, "kg");

const MU * const MU::MilliSeconds = new MU(0.001L, SU::Seconds, "ms");
const MU * const MU::Seconds = new MU(1.0L, SU::Seconds, "s");
const MU * const MU::Minutes = new MU(60.0L, SU::Seconds, "min");
const MU * const MU::Hours = new MU(60.0L * 60.0L, SU::Seconds, "h");

const MU * const MU::Kelvins = new MU(1.0L, SU::Kelvins, "K°");

const MU * const MU::Radians = new MU(1.0L, SU::Radians , "rad");
const MU * const MU::Degrees = new MU(2.0L * M_PI/ 360.0L, SU::Radians , "deg");

