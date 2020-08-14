#ifndef ENGINECALC_GEARBOX_H
#define ENGINECALC_GEARBOX_H

#include "../../math/function/function.h"

#include <cstdint>
#include <vector>

namespace engc::model {
class Gearbox {
private:
    const std::vector<math::fret_t> gearRatios;
    uint_fast8_t currentGear;

    static const std::string ROTATING_SPEED;

public:

    Gearbox(const std::vector<math::fret_t>& gearRatios);
    virtual ~Gearbox();

    virtual std::shared_ptr<math::Function> rotationSpeedF() const;
    virtual std::shared_ptr<math::Function> rotationSpeedReverseF() const;
    virtual int gearCount() const;
    virtual void shiftToGear(const uint_fast8_t& gear);
    virtual void shiftToReverse();
};
};


#endif //ENGINECALC_GEARBOX_H
