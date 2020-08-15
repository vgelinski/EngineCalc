#ifndef COMMON_UNITS_H
#define COMMON_UNITS_H

#include "units.h"

#define CU const std::shared_ptr<CompoundUnit>

namespace engc::physics {
class CommonUnits {
    public:
    CommonUnits();
    class LengthUnits {
    public:
        LengthUnits();
        CU Hundredthmm;
        CU mm;
        CU cm;
        CU m;
        CU Km;
        CU Inch;
    };
    const LengthUnits * Length;
    class AreaUnits {
    public:
        AreaUnits(const LengthUnits* Length);
        CU mm2;
        CU m2;
    };
    const AreaUnits * Area;
    class VolumeUnits {
    public:
        VolumeUnits(const LengthUnits* Length, const AreaUnits * Area);
        CU mm3;
        CU cm3;
        CU l;
        CU m3;
    };
    const VolumeUnits * Volume;
    class MassUnits {
    public:
        MassUnits();
        CU g;
        CU Kg;
    };
    const MassUnits * Mass;
    class TimeUnits {
    public:
        TimeUnits();
        CU ms;
        CU s;
        CU min;
        CU h;
    };
    const TimeUnits * Time;
    class TemperatureUnits {
    public:
        TemperatureUnits();
        CU K;
    };
    const TemperatureUnits * Temperature;
    class AngleUnits {
    public:
        AngleUnits();
        CU rad;
        CU deg;
        CU round;
    };
    const AngleUnits * Angle;
    class SpeedUnits {
    public:
        SpeedUnits(const LengthUnits* Length, const AngleUnits * Angle, const TimeUnits * Time);
        CU KmPh;
        CU mPs;
        CU radPs;
        CU rpm;
    };
    const SpeedUnits * Speed;
    class AccelerationUnits {
    public:
        AccelerationUnits(const LengthUnits* Length, const TimeUnits * Time);
        CU mps2;
        CU g;
    };
    const AccelerationUnits * Acceleration;
    class ForceUnits {
    public:
        ForceUnits(const AccelerationUnits * Acceleration, const MassUnits * Mass);
        CU N;
        CU KN;
        CU Kgf;
    };
    const ForceUnits * Force;
    class TorqueUnits {
    public:
        TorqueUnits(const LengthUnits* Length, const ForceUnits * Force);
        CU Nm;
    };
    const TorqueUnits * Torque;
    class WorkUnits {
    public:
        WorkUnits(const LengthUnits* Length, const ForceUnits * Force);
        CU J;
        CU KJ;
    };
    const WorkUnits * Work;
    class PowerUnits {
    public:
        PowerUnits(const WorkUnits * Work, const TimeUnits * Time);
        CU W;
        CU KW;
        CU HP;
    };
    const PowerUnits * Power;
    class EnergyUnits {
    public:
        EnergyUnits(const LengthUnits* Length, const ForceUnits * Force, const PowerUnits * Power, const TimeUnits * Time);
        CU J;
        CU KJ;
        CU Wh;
        CU KWh;
    };
    const EnergyUnits * Energy;
    static const CommonUnits * Get();
};
}; //end namespace
#undef CU
#endif //COMMON_UNITS_H
