#ifndef ENGINECALC_COMMON_GEARBOXES_H
#define ENGINECALC_COMMON_GEARBOXES_H

#include "gearbox.h"

namespace engc::model {
class CommonGearboxes {

public:
    class VAZ {
    public:
        static std::shared_ptr<Gearbox> VAZ_2101();
        static std::shared_ptr<Gearbox> VAZ_2105();
        static std::shared_ptr<Gearbox> VAZ_2106();
        static std::shared_ptr<Gearbox> R1();
        static std::shared_ptr<Gearbox> R2();
        static std::shared_ptr<Gearbox> R3();
        static std::shared_ptr<Gearbox> R4();
    };
};
};


#endif //ENGINECALC_COMMON_GEARBOXES_H
