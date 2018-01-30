#ifndef FUNCTION_H
#define FUNCTION_H

#include <map>
#include <string>

class Function {

public:
//    virtual ~Function();
    virtual double value(const std::map<std::string, double> &params) const = 0;
};

#endif
