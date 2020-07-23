#include "common_units.h"

using namespace std;
using namespace engc::physics;

#define SU SimpleUnit
#define CMN CommonUnits

#define LENGTH const shared_ptr<CompoundUnit> CommonUnits::Length
#define AREA const shared_ptr<CompoundUnit> CommonUnits::Area
#define VOLUME const shared_ptr<CompoundUnit> CommonUnits::Volume
#define MASS const shared_ptr<CompoundUnit> CommonUnits::Mass
#define TIME const shared_ptr<CompoundUnit> CommonUnits::Time
#define TEMPERATURE const shared_ptr<CompoundUnit> CommonUnits::Temperature
#define ANGLE const shared_ptr<CompoundUnit> CommonUnits::Angle
#define SPEED const shared_ptr<CompoundUnit> CommonUnits::Speed
#define ACC const shared_ptr<CompoundUnit> CommonUnits::Acceleration
#define FORCE const shared_ptr<CompoundUnit> CommonUnits::Force
#define TORQUE const shared_ptr<CompoundUnit> CommonUnits::Torque
#define WORK const shared_ptr<CompoundUnit> CommonUnits::Work
#define POWER const shared_ptr<CompoundUnit> CommonUnits::Power
#define ENERGY const shared_ptr<CompoundUnit> CommonUnits::Energy
#define MK_UNIT make_shared<CompoundUnit>

LENGTH::Hundredthmm = MK_UNIT(SU::HundredthMilliMeters);
LENGTH::mm = MK_UNIT(SU::MilliMeters);
LENGTH::cm = CMN::Length::mm->withName("cm", 10);
LENGTH::m = MK_UNIT(SU::Meters);
LENGTH::Km = MK_UNIT(SU::KiloMeters);
LENGTH::Inch = CMN::Length::mm->withName("in", 25.4L);

AREA::mm2 = CMN::Length::mm * CMN::Length::mm;
AREA::m2 = CMN::Length::m * CMN::Length::m;

VOLUME::mm3 = CMN::Area::mm2 * CMN::Length::mm;
VOLUME::cm3 = (CMN::Length::cm * CMN::Length::cm * CMN::Length::cm)->withName("cm3");
VOLUME::l = CMN::Volume::cm3->withName("l", 1000);
VOLUME::m3 = CMN::Area::m2 * CMN::Length::m;

MASS::g = MK_UNIT(SU::Grams);
MASS::Kg = MK_UNIT(SU::Kilograms);

TIME::ms = MK_UNIT(SU::MilliSeconds);
TIME::s = MK_UNIT(SU::Seconds);
TIME::min = MK_UNIT(SU::Minutes);
TIME::h = MK_UNIT(SU::Hours);

TEMPERATURE::K = MK_UNIT(SU::Kelvins);

ANGLE::rad = MK_UNIT(SU::Radians);
ANGLE::deg = MK_UNIT(SU::Degrees);
ANGLE::round = MK_UNIT(SU::Rounds);

SPEED::KmPh = CMN::Length::Km / CMN::Time::h;
SPEED::mPs = CMN::Length::m / CMN::Time::s;
SPEED::radPs = CMN::Angle::rad / CMN::Time::s;
SPEED::rpm = (CMN::Angle::round / CMN::Time::min)->withName("rpm");

ACC::mps2 = CMN::Length::m / (CMN::Time::s * CMN::Time::s);
ACC::g = CMN::Acceleration::mps2->withName("g", 9.8l);

FORCE::N = (CMN::Acceleration::mps2 * CMN::Mass::Kg)->withName("N");
FORCE::KN = CMN::Force::N->withName("KN", 1000);
FORCE::Kgf = (CMN::Acceleration::g * CMN::Mass::Kg)->withName("Kgf");

TORQUE::Nm = CMN::Force::N * CMN::Length::m;

WORK::J = CMN::Force::N * CMN::Length::m;
WORK::KJ = CMN::Work::J->withName("KJ", 1000);

POWER::W = CMN::Work::J / CMN::Time::s;
POWER::KW = CMN::Power::W->withName("KW", 1000);
POWER::HP = CMN::Power::KW->withName("HP", 0.745699872L);

ENERGY::J = CMN::Force::N * CMN::Length::m;
ENERGY::KJ = CMN::Energy::J->withName("KJ", 1000);
ENERGY::Wh = (CMN::Power::W * CMN::Time::h)->withName("Wh");
ENERGY::KWh = CMN::Energy::Wh->withName("KWh", 1000);
