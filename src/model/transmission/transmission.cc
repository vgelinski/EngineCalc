#include "transmission.h"

#include "../../math/constant.h"
#include "../../math/identity.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;


const string Transmission::ROTATING_SPEED = "rotationSpeed";

Transmission::Transmission(
        const shared_ptr<Tyre> leftTyre,
        const shared_ptr<Tyre> rightTyre,
        const shared_ptr<Differential> diff,
        const shared_ptr<Gearbox> gearbox
) : leftTyre(leftTyre),
    rightTyre(rightTyre),
    diff(diff),
    gearbox(gearbox)
{}

Transmission::~Transmission(){}

shared_ptr<Function> Transmission::speedF() const {
    auto gearBoxF = gearbox->rotationSpeedF();
    return make_shared<Identity>(ROTATING_SPEED) / make_shared<Constant>(0);
}