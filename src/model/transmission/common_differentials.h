#ifndef ENGINECALC_COMMON_DIFFERENTIALS_H
#define ENGINECALC_COMMON_DIFFERENTIALS_H

#include "differential.h"

namespace engc::model {
class CommonDifferentials {
public:
    class VAZ {
    public:
        static std::shared_ptr<Differential> VAZ_2101();
        static std::shared_ptr<Differential> VAZ_2102();
        static std::shared_ptr<Differential> VAZ_2103();
        static std::shared_ptr<Differential> VAZ_2106();
    };

};
};


#endif //ENGINECALC_COMMON_DIFFERENTIALS_H
