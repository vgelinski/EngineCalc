#include "custom_function.h"

using namespace std;
using namespace engc::math;

#define CF CustomFunction

CF::CustomFunction(
        const function<fret_t(const fparams_t&)>& cf,
        const fvariables_t& vars,
        const string& representation
) : custF(cf), vars(vars), representation(representation) {}

CF::~CustomFunction() {}

fret_t CF::value(const fparams_t& params) const {
    return custF(params);
}

string CF::toStringImpl() const {
    return representation;
};

fvariables_t CF::variables() const {
    return vars;
}
