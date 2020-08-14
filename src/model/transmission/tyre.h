#ifndef ENGINECALC_TYRE_H
#define ENGINECALC_TYRE_H

#include "../../math/function/function.h"
#include "../../physics/value.h"

namespace engc::model {

#define VAL std::shared_ptr<physics::Value>

class Tyre {
private:

    static const std::string DIAMETER;
    static const std::string WIDTH;
    static const std::string HEIGHT;
    static const std::string ROTATING_SPEED;
    static const std::string SPEED;

    const VAL diameter;
    const VAL width;
    const VAL height;

public:

    Tyre(const math::fret_t& widthMM, const math::fret_t& heightPerc, const math::fret_t& diameterInch);
    virtual ~Tyre();

    virtual std::shared_ptr<math::Function> speedF() const;
    virtual std::shared_ptr<math::Function> rotationF() const;

private:

    virtual std::shared_ptr<math::Function> radiusF() const;

};

#undef VAL
};


#endif //ENGINECALC_TYRE_H
