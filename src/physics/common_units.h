#ifndef COMMON_UNITS_H
#define COMMON_UNITS_H

#include "units.h"

#define CU static const std::shared_ptr<CompoundUnit>

namespace engc::physics {
class CommonUnits {
public:
    class Length {
    public:
        CU Hundredthmm;
        CU mm;
        CU cm;
        CU m;
        CU Km;
    };
    class Area {
    public:
        CU mm2;
        CU m2;
    };
    class Volume {
    public:
        CU mm3;
        CU cm3;
        CU l;
        CU m3;
    };
    class Mass {
    public:
        CU g;
        CU Kg;
    };
    class Time {
    public:
        CU ms;
        CU s;
        CU min;
        CU h;
    };
    class Temperature {
    public:
        CU K;
    };
    class Angle {
    public:
        CU rad;
        CU deg;
        CU round;
    };
    class Speed {
    public:
        CU KmPh;
        CU mPs;
        CU radPs;
        CU rpm;
    };
    class Acceleration {
    public:
        CU mps2;
        CU g;
    };
    class Force {
    public:
        CU N;
        CU KN;
        CU Kgf;
    };
    class Torque {
        CU Nm;
    };
    class Work {
    public:
        CU J;
        CU KJ;
    };
    class Power {
    public:
        CU W;
        CU KW;
        CU HP;
    };
    class Energy {
    public:
        CU J;
        CU KJ;
        CU Wh;
        CU KWh;
    };
};
}; //end namespace
#undef CU
#endif //COMMON_UNITS_H
