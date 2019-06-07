#include "integral.h"

#include <cmath>

#include "constant.h"

using namespace std;
using namespace engc::math;

#define IC IntegralCalculator
#define MTI Integral

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
    auto intgr = make_shared<Integral>(f, a, b, param, errBound);
    return start < end ? intgr : (make_shared<Constant>(-1) * intgr);
}

IC::MTI::Integral(
        shared_ptr<const Function> f,
        fret_t start, fret_t end,
        const string &param,
        fret_t errBound) : 
            start(start), end(end), errBound(errBound),
            function(f), param(param) {}

IC::MTI::~Integral() {}

fret_t IC::MTI::value(const fparams_t &params) const {
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

fvariables_t IC::MTI::variables() const {
    fvariables_t vars = function->variables();
    vars.erase(param);
    return vars;
}

fret_t IC::MTI::calculateForN(int n, fparams_t params) const {
    fret_t sum = 0;
    fret_t h = (end - start) / n;
    int oneIterN = n / THREAD_COUNT;
    for (int i = 0; i <= THREAD_COUNT; i++) {
        fret_t a = start + i * oneIterN * h;
        fret_t b = min(a + oneIterN * h, end);
        sum += calculateAB(a, b, h, params);
    }
    params[param] = start;
    fret_t f0 = (*function)(params);
    params[param] = end;
    fret_t fn = (*function)(params);
    fret_t result = h * sum - h * (fn - f0) / 2;
    return result;
}

fret_t IC::MTI::calculateAB(const fret_t &a, const fret_t &b,
        const fret_t &step, fparams_t params) const {

    fret_t sum = 0;
    for(fret_t curr = a; curr < b; curr += step) {
        params[param] = curr;
        sum += (*function)(params);
    }
    return sum;
}

