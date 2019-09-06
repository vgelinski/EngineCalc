#include "custom_function.h"

using namespace std;
using namespace engc::math;

#define CF CustomFunction

CF::CustomFunction(const function<fret_t(fparams_t)>& cf, const fvariables_t& vars)
        : custF(cf), vars(vars) {}

CF::~CustomFunction() {}

fret_t CF::value(const fparams_t& params) const {
    return custF(params);
}

fvariables_t CF::variables() const {
    return vars;
}
