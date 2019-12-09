#include "implicit_function.h"

#include <cmath>

using namespace std;
using namespace engc::math;

#define IF ImplicitFunction

IF::ImplicitFunction(
        const shared_ptr <Function>& F,
        const string& pName,
        const fret_t& start,
        const fret_t& end,
        const fret_t& err_bound
) : F(F), pName(pName), start(start), end(end), err_bound(err_bound) {}

IF::~ImplicitFunction() {}

fret_t IF::value(const fparams_t& params) const {
    fparams_t mutableParams = params;
    return solveFor(start, end, mutableParams);
}

fvariables_t IF::variables() const {
    auto vars = F->variables();
    vars.erase(pName);
    return vars;
}

bool IF::equals(const fret_t &a, const fret_t &b) const {
    return fabs(a - b) < err_bound;
}

inline fret_t IF::val(fparams_t &params, const fret_t& arg) const {
    params[pName] = arg;
    return (*F)(params);
}

fret_t IF::solveFor(const fret_t& left, const fret_t& right, fparams_t& params) const {
    auto lVal = val(params, left);
    if (equals(lVal, 0.0L)) return left;

    auto rVal = val(params, right);
    if (equals(rVal, 0.0L)) return right;

    auto middle = (left + right) / 2.0L;
    auto midVal = val(params, middle);
    if (equals(midVal, 0.0L)) return middle;

    if (lVal * midVal < 0.0L) { // different signs
        return solveFor(left, middle, params);
    } else {
        return solveFor(middle, right, params);
    }
}
