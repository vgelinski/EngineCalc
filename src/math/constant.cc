#include "constant.h"

using namespace std;
using namespace engc::math;

Constant::Constant(const double &val) : val(val){};

Constant::~Constant() {};

double Constant::value(const map<string, double> &params) const {
    return val;
};
