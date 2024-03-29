#include "transmission.h"

#include "../../math/function/constant.h"
#include "../../math/function/identity.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;


const string Transmission::ROTATING_SPEED = "rotationSpeed";
const string Transmission::SPEED = "speed";

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
    auto gearboxF = gearbox->rotationSpeedF();
    auto diffF = diff->rotationSpeedF()->substitute(ROTATING_SPEED, "diff");
    auto leftTyreF = leftTyre->speedF()->substitute(ROTATING_SPEED, "left");
    auto rightTyreF = rightTyre->speedF()->substitute(ROTATING_SPEED, "right");
    auto leftSpeedF = leftTyreF->compose(diffF, "left")->compose(gearboxF, "diff");
    auto rightSpeedF = rightTyreF->compose(diffF, "right")->compose(gearboxF, "diff");
    return (leftSpeedF + rightSpeedF) / make_shared<Constant>(2);
}

shared_ptr<Function> Transmission::rotationF() const {
    auto leftRotF = leftTyre->rotationF();
    auto rightRotF = rightTyre->rotationF();
    auto diffRotF = (leftRotF + rightRotF) / make_shared<Constant>(2);
    auto gearRotF = diff->rotationSpeedReverseF()->compose(diffRotF, ROTATING_SPEED);
    auto engineRotF = gearbox->rotationSpeedReverseF()->compose(gearRotF, ROTATING_SPEED);

    return engineRotF;
}