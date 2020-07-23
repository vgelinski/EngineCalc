#ifndef ENGINECALC_TYRE_H
#define ENGINECALC_TYRE_H

#include "../../math/function.h"
#include "../../physics/value.h"

namespace engc::model {

#define VAL std::shared_ptr<physics::Value>

class Tyre {
private:

    static const std::string RADIUS;
    static const std::string WIDTH;
    static const std::string HEIGHT;
    static const std::string ROTATING_SPEED;

    const VAL radius;
    const VAL width;
    const VAL height;

public:

    Tyre(const math::fret_t& widthMM, const math::fret_t& heightPerc, const math::fret_t& radiusInch);
    virtual ~Tyre();

    virtual std::shared_ptr<math::Function> speedF() const;

};

#undef VAL
};


#endif //ENGINECALC_TYRE_H
