#include "integral.h"

using namespace std;
using namespace engc::math;

shared_ptr<Function> IntegralCalculator::integrate(
        shared_ptr<Function> f,
        double start, double end,
        const string &param,
        double errBound,
        int threadCount) {

    return make_shared<SingleThreadIntegral>(f, start, end, param, errBound);
}

IntegralCalculator::SingleThreadIntegral::SingleThreadIntegral(
        shared_ptr<Function> f,
        double start, double end,
        const string &param,
        double errBound) {}

IntegralCalculator::SingleThreadIntegral::~SingleThreadIntegral() {}

double IntegralCalculator::SingleThreadIntegral::
        value(const fparams_t &params) const {
    return 0;
}

fvariables_t IntegralCalculator::SingleThreadIntegral::variables() const {
    return fvariables_t({});
}
