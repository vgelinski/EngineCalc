#include "common_units.h"

using namespace std;
using namespace engc::physics;

#define SU SimpleUnitValues
#define CMN CommonUnits

#define MK_UNIT make_shared<CompoundUnit>

const CommonUnits * CommonUnits::Get() {
    static auto instance = new CommonUnits();
    return instance;
}

CMN::CMN() : Length(new LengthUnits()),
             Area(new AreaUnits(Length)),
             Volume(new VolumeUnits(Length, Area)),
             Mass(new MassUnits()),
             Time(new TimeUnits()),
             Temperature(new TemperatureUnits()),
             Angle(new AngleUnits()),
             Speed(new SpeedUnits(Length, Angle, Time)),
             Acceleration(new AccelerationUnits(Length, Time)),
             Force(new ForceUnits(Acceleration, Mass)),
             Torque(new TorqueUnits(Length, Force)),
             Work(new WorkUnits(Length, Force)),
             Power(new PowerUnits(Work, Time)),
             Energy(new EnergyUnits(Length, Force, Power, Time)) {}


CMN::LengthUnits::LengthUnits() : 
    Hundredthmm(MK_UNIT(SU::Get()->HundredthMilliMeters)),
    mm(MK_UNIT(SU::Get()->MilliMeters)),
    cm(mm->withName("cm", 10)),
    m(MK_UNIT(SU::Get()->Meters)),
    Km(MK_UNIT(SU::Get()->KiloMeters)),
    Inch(mm->withName("in", 25.4L)) {}

CMN::AreaUnits::AreaUnits(const LengthUnits* Length) :
    mm2(Length->mm * Length->mm),
    m2(Length->m * Length->m) {}

CMN::VolumeUnits::VolumeUnits(const LengthUnits* Length, const AreaUnits * Area) :
    mm3(Area->mm2 * Length->mm),
    cm3((Length->cm * Length->cm * Length->cm)->withName("cm3")),
    l(cm3->withName("l", 1000)),
    m3(Area->m2 * Length->m) {}

CMN::MassUnits::MassUnits() :
    g(MK_UNIT(SU::Get()->Grams)),
    Kg(MK_UNIT(SU::Get()->Kilograms)) {}

CMN::TimeUnits::TimeUnits() :
    ms(MK_UNIT(SU::Get()->MilliSeconds)),
    s(MK_UNIT(SU::Get()->Seconds)),
    min(MK_UNIT(SU::Get()->Minutes)),
    h(MK_UNIT(SU::Get()->Hours)) {}

CMN::TemperatureUnits::TemperatureUnits() :
    K(MK_UNIT(SU::Get()->Kelvins)) {}

CMN::AngleUnits::AngleUnits() :
    rad(MK_UNIT(SU::Get()->Radians)),
    deg(MK_UNIT(SU::Get()->Degrees)),
    round(MK_UNIT(SU::Get()->Rounds)) {}

CMN::SpeedUnits::SpeedUnits(const LengthUnits* Length, const AngleUnits * Angle, const TimeUnits * Time) :
    KmPh(Length->Km / Time->h),
    mPs(Length->m / Time->s),
    radPs(Angle->rad / Time->s),
    rpm((Angle->round / Time->min)->withName("rpm")) {}

CMN::AccelerationUnits::AccelerationUnits(const LengthUnits* Length, const TimeUnits * Time) :
    mps2(Length->m / (Time->s * Time->s)),
    g(mps2->withName("g", 9.8l)) {}

CMN::ForceUnits::ForceUnits(const AccelerationUnits * Acceleration, const MassUnits * Mass) :
    N((Acceleration->mps2 * Mass->Kg)->withName("N")),
    KN(N->withName("KN", 1000)),
    Kgf((Acceleration->g * Mass->Kg)->withName("Kgf")) {}

CMN::TorqueUnits::TorqueUnits(const LengthUnits* Length, const ForceUnits * Force) :
    Nm(Force->N * Length->m) {}

CMN::WorkUnits::WorkUnits(const LengthUnits* Length, const ForceUnits * Force) :
    J(Force->N * Length->m),
    KJ(J->withName("KJ", 1000)) {}

CMN::PowerUnits::PowerUnits(const WorkUnits * Work, const TimeUnits * Time) :
    W(Work->J / Time->s),
    KW(W->withName("KW", 1000)),
    HP(KW->withName("HP", 0.745699872L)) {}

CMN::EnergyUnits::EnergyUnits(const LengthUnits* Length, const ForceUnits * Force, const PowerUnits * Power, const TimeUnits * Time) :
    J(Force->N * Length->m),
    KJ(J->withName("KJ", 1000)),
    Wh((Power->W * Time->h)->withName("Wh")),
    KWh(Wh->withName("KWh", 1000)) {}

