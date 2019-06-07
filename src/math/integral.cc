#include "integral.h"

#include <cmath>

#include "constant.h"

using namespace std;
using namespace engc::math;

#define IC IntegralCalculator
#define STI SingleThreadIntegral

shared_ptr<Function> IC::integrate(
        shared_ptr<const Function> f,
        fret_t start, fret_t end,
        const string &param,
        fret_t errBound,
        int threadCount) {

    if (abs(start - end) < errBound / 2) {
        return make_shared<Constant>(0);
    }
    fret_t a = min(start, end);
    fret_t b = max(start, end);
    auto intgr = make_shared<SingleThreadIntegral>(f, a, b, param, errBound);
    return start < end ? intgr : (make_shared<Constant>(-1) * intgr);
}

IC::STI::SingleThreadIntegral(
        shared_ptr<const Function> f,
        fret_t start, fret_t end,
        const string &param,
        fret_t errBound) : 
            start(start), end(end), errBound(errBound),
            function(f), param(param) {}

IC::STI::~SingleThreadIntegral() {}

fret_t IC::STI::value(const fparams_t &params) const {
    int n = (end - start) / errBound;
    fret_t result = calculateForN(n, params);
    fret_t newResult = calculateForN(n*2, params);
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

fret_t IC::STI::calculateForN(int n, fparams_t params) const {
    fret_t sum = 0;
    fret_t h = (end - start) / n;
    for (int i = 0; i <= n; i++) {
        fret_t xi = start + i * h;
        params[param] = xi;
        sum += (*function)(params);
    }
    params[param] = start;
    fret_t f0 = (*function)(params);
    params[param] = end;
    fret_t fn = (*function)(params);
    fret_t result = h * sum - h * (fn - f0) / 2;
    return result;
}
