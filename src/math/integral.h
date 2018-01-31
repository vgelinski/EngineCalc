#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <memory>

#include "function.h"

namespace std{

class IntegralCalculator {

public:

    static shared_ptr<Function> integrate(shared_ptr<Function> f,
                                          double start, double end,
                                          const string &param,
                                          int riemannSumCount = 1000);

private:
    class SingleThreadIntegral : public Function {

    private:

    public:

        virtual double value(const map<string, double> &params) const override;
    };
};
}
#endif
