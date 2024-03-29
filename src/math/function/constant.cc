#include "constant.h"

using namespace std;
using namespace engc::math;

Constant::Constant(const fret_t& val) : val(val){};

Constant::~Constant() {};

fret_t Constant::value(const fparams_t& params) const {
    return val;
};

string Constant::toStringImpl() const {
    char buffer[1024];
    sprintf(buffer, "%Lg", val);
    auto valStr = string(buffer);
    return val >= 0 ? valStr : "\\left(" + valStr + "\\right)";
};

fvariables_t Constant::variables() const {
    return fvariables_t();
}
