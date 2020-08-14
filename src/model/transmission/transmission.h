#ifndef ENGINECALC_TRANSMISSION_H
#define ENGINECALC_TRANSMISSION_H

#include "differential.h"
#include "gearbox.h"
#include "tyre.h"
#include "../../math/function/function.h"

namespace engc::model {
class Transmission {
private:
    const std::shared_ptr<Tyre> leftTyre;
    const std::shared_ptr<Tyre> rightTyre;
    const std::shared_ptr<Differential> diff;

    static const std::string ROTATING_SPEED;
    static const std::string SPEED;

public:
    const std::shared_ptr<Gearbox> gearbox; //public to allow shifting gears

    Transmission(
            const std::shared_ptr<Tyre> leftTyre,
            const std::shared_ptr<Tyre> rightTyre,
            const std::shared_ptr<Differential> diff,
            const std::shared_ptr<Gearbox> gearbox
    );
    virtual ~Transmission();

    virtual std::shared_ptr<math::Function> speedF() const;
    virtual std::shared_ptr<math::Function> rotationF() const;

};
};


#endif //ENGINECALC_TRANSMISSION_H
