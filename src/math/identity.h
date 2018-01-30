#ifndef IDENTITY_H
#define IDENTITY_H

#include "function.h"

#include <string>
#include <map>

namespace std{
class Identity : public Function {
private:

    string paramName;

public:

    Identity(const string &paramName);
    virtual ~Identity();
    virtual double value(const map<string, double> &params) const override;
};
}

#endif
