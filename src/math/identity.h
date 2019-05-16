#ifndef IDENTITY_H
#define IDENTITY_H

#include "function.h"

#include <string>
#include <map>

class Identity : public Function {
private:

    std::string paramName;

public:

    Identity(const std::string &paramName);
    virtual ~Identity();
    virtual double value(const std::map<std::string, double> &params) const override;
};

#endif
