#include "differential.h"

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
    fret_t dx = errBound / 2;
    fret_t result = calculateForDx(dx, params);
    fret_t newResult = calculateForDx(dx / 2, params);
    while(abs(result - newResult) > errBound / 2) {
        result = newResult;
        dx /= 2;
        newResult = calculateForDx(dx /2, params);
    }
    return newResult;
}

fvariables_t DC::Differential::variables() const {
    return function->variables();
}

fret_t DC::Differential::calculateForDx(const fret_t& dx, fparams_t params) const {
    auto fx = function->operator()(params);
    params[param] += dx;
    auto fdx = function->operator()(params);
    auto df = fdx - fx;
    return df/dx;
}
