#include "differential.h"

#include <cmath>

using namespace std;
using namespace engc::math;

#define DC DifferentialCalculator


shared_ptr<Function> DC::derive(
        shared_ptr<const Function> f,
        const string& param,
        fret_t errBound) {

    return make_shared<Differential>(f, param, errBound);
}

DC::Differential::Differential(shared_ptr<const Function> f, const string& param, fret_t errBound)
        : function(f), param(param), errBound(errBound) {}

DC::Differential::~Differential() {}


fret_t DC::Differential::value(const fparams_t& params) const {
    fret_t dx = errBound * 4.0L;
    fret_t result = calculateForDx(dx, params);
    fret_t newResult = calculateForDx(dx / 2.0L, params);
    while(fabs(result - newResult) > errBound / 2) {
        result = newResult;
        dx /= 2.0L;
        newResult = calculateForDx(dx /2.0L, params);
    }
    return newResult;
}

fvariables_t DC::Differential::variables() const {
    return function->variables();
}

fret_t DC::Differential::calculateForDx(const fret_t& dx, fparams_t params) const {
    params[param] -= dx / 2.0L;
    auto fx = (*function)(params);
    params[param] += dx;
    auto fdx = (*function)(params);
    auto df = fdx - fx;
    return df/dx;
}
