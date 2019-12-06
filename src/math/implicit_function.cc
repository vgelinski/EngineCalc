#include "implicit_function.h"

using namespace std;
using namespace engc::math;

#define IF ImplicitFunction

IF::ImplicitFunction(
        const shared_ptr <Function> &F,
        const string &pName,
        const fret_t &start,
        const fret_t &end,
        const fret_t &err_bound
) : F(F), pName(pName), start(start), end(end), err_bound(err_bound) {}

IF::~ImplicitFunction() {}

fret_t IF::value(const fparams_t& params) const {
    return 0;
}

fvariables_t IF::variables() const {
    fvariables_t {pName};
}
