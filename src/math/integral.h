#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <memory>

#include "function.h"

namespace engc::math{

class IntegralCalculator {

public:

    static std::shared_ptr<Function> integrate(std::shared_ptr<Function> f,
                                          double start, double end,
                                          const std::string &param,
                                          int riemannSumCount = 1000);

private:
    class SingleThreadIntegral : public Function {

    private:

    public:

        virtual double value(const std::map<std::string, double> &params) const override;
    };
};
}; //end namespace
#endif
