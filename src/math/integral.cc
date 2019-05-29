#include "integral.h"

using namespace std;
using namespace engc::math;

shared_ptr<Function> IntegralCalculator::integrate(shared_ptr<Function> f,
        double start, double end, const string &param, int riemannSumCount) {
    return make_shared<SingleThreadIntegral>();
}

double IntegralCalculator::SingleThreadIntegral::
        value(const map<string, double> &params) const {
    return 0;
}
