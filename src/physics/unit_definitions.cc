#include "units.h"

using namespace engc::physics;
using namespace std;

#define SUT SimpleUnitType
#define SU  SimpleUnit


const SU * const SU::Meters = new SU(SUT::Length, "m");
const SU * const SU::Kilograms = new SU(SUT::Mass, "kg");
const SU * const SU::Seconds = new SU(SUT::Time, "s");
const SU * const SU::Kelvins = new SU(SUT::Temperature, "K°");
