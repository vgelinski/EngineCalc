#ifndef SUSPENSION_CALCULATOR_H
#define SUSPENSION_CALCULATOR_H


#include "../../math/function/function.h"
#include "../../physics/value.h"

namespace engc::tools {
class SuspensionCalculator {
private:
    static const std::shared_ptr<physics::Value> CD;
    static const std::shared_ptr<physics::Value> Xd;
    static const std::shared_ptr<physics::Value> Yd;
    static const std::shared_ptr<physics::Value> Ya_MIN;
    static const std::shared_ptr<physics::Value> Ya_MAX;
    static const std::shared_ptr<physics::Value> R_MIN;
    static const std::shared_ptr<physics::Value> R_MAX;
    static const std::shared_ptr<physics::Value> r_MIN;
    static const std::shared_ptr<physics::Value> r_MAX;
    static const std::shared_ptr<physics::Value> ERR_BOUND;

    static std::shared_ptr<math::Function> sq(const std::shared_ptr<math::Function>& f);

public:
    static void calculateRearSuspensionOptimalBarLengths();

};
};


#endif //SUSPENSION_CALCULATOR_H
