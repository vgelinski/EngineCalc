#include "constant.h"

using namespace std;
using namespace engc::math;

Constant::Constant(const fret_t &val) : val(val){};

Constant::~Constant() {};

fret_t Constant::value(const fparams_t &params) const {
    return val;
};

fvariables_t Constant::variables() const {
    return fvariables_t();
}
