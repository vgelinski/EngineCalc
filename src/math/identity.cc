#include "identity.h"

using namespace std;

Identity::Identity(const string &paramName) : paramName(paramName){};

Identity::~Identity() {};

double Identity::value(const map<string, double> &params) const {
    return params.at(paramName);
};
