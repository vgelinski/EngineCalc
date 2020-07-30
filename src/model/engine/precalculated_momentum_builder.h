#ifndef ENGINECALC_PRECALCULATED_MOMENTUM_BUILDER_H
#define ENGINECALC_PRECALCULATED_MOMENTUM_BUILDER_H

#include "../../math/function.h"
#include "../../physics/value.h"

namespace engc::model {

#define VAL std::shared_ptr<physics::Value>
class PrecalculatedMomentumBuilder {
private:
    VAL maxMomentumRpm;
    VAL maxMomentum;
    VAL maxPowerRpm;
    VAL maxPower;

public:
    PrecalculatedMomentumBuilder();
    virtual ~PrecalculatedMomentumBuilder();

    virtual void setMaxMomentum(VAL rpm, VAL momentum);
    virtual void setMaxPower(VAL rpm, VAL power);

    virtual std::shared_ptr<math::Function> calculateMomentum() const;
    virtual std::shared_ptr<math::Function> calculatePower() const;
};
#undef VAL
};


#endif //ENGINECALC_PRECALCULATED_MOMENTUM_BUILDER_H
