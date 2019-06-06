#include "integral.h"

#include <cmath>

#include "constant.h"

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

    if (abs(start - end) < errBound / 2) {
        return make_shared<Constant>(0);
    }
    double a = min(start, end);
    double b = max(start, end);
    auto intgr = make_shared<SingleThreadIntegral>(f, a, b, param, errBound);
    return start < end ? intgr : (make_shared<Constant>(-1) * intgr);
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
    while(abs(result - newResult) > errBound / 2) {
        result = newResult;
        n *= 2;
        newResult = calculateForN(n*2, params);
    }
    return result;
}

fvariables_t IC::STI::variables() const {
    fvariables_t vars = function->variables();
    vars.erase(param);
    return vars;
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
    return result;
}
