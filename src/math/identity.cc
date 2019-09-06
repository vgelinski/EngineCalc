#include "identity.h"

using namespace std;
using namespace engc::math;

Identity::Identity(const string& paramName) : paramName(paramName){};

Identity::~Identity() {};

fret_t Identity::value(const fparams_t& params) const {
    return params.at(paramName);
};

fvariables_t Identity::variables() const {
    fvariables_t ret({paramName});
    return ret;
}
