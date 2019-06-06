#include "integral.h"

#include <cmath>

using namespace std;
using namespace engc::math;

#define IC IntegralCalculator
#define STI SingleThreadIntegral

shared_ptr<Function> IC::integrate(
        shared_ptr<const Function> f,
        double start, double end,
        const string &param,
        double errBound,
        int threadCount) {

    return make_shared<SingleThreadIntegral>(f, start, end, param, errBound);
}

IC::STI::SingleThreadIntegral(
        shared_ptr<const Function> f,
        double start, double end,
        const string &param,
        double errBound) : 
            start(start), end(end), errBound(errBound),
            function(f), param(param) {}

IC::STI::~SingleThreadIntegral() {}

double IC::STI::value(const fparams_t &params) const {
    int n = (end - start) / errBound;
    double result = calculateForN(n, params);
    double newResult = calculateForN(n*2, params);
    while(abs(result - newResult) > errBound) {
        result = newResult;
        n *= 2;
        newResult = calculateForN(n*2, params);
    }
    return result;
}

fvariables_t IC::STI::variables() const {
    return fvariables_t({});
}

double IC::STI::calculateForN(int n, fparams_t params) const {
    double sum = 0;
    double h = (end - start) / n;
    for (int i = 0; i <= n; i++) {
        double xi = start + i * h;
        params[param] = xi;
        sum += (*function)(params);
    }
    params[param] = start;
    double f0 = (*function)(params);
    params[param] = end;
    double fn = (*function)(params);
    double result = h * sum - h * (fn - f0) / 2;
    //printf("n=%d,\tintgr=%f\n", n, result);
    return result;
}
