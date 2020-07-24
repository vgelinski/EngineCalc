#ifndef ENGINECALC_DIFFERENTIAL_H
#define ENGINECALC_DIFFERENTIAL_H

#include "../../math/function.h"

namespace engc::model {
class Differential {

private:

    const math::fret_t ratio;

    static const std::string ROTATING_SPEED;

public:

    Differential(const math::fret_t& ratio);
    virtual ~Differential();

    virtual std::shared_ptr<math::Function> rotationSpeedF() const;
    virtual std::shared_ptr<math::Function> rotationSpeedReverseF() const;

};

};


#endif //ENGINECALC_DIFFERENTIAL_H
