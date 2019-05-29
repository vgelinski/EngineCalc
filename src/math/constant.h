#ifndef CONSTANT_H
#define CONSTANT_H

#include "function.h"

#include <string>
#include <map>

namespace engc::math {

/** \brief Клас, моделиращ константа.
 *
 */
class Constant : public Function {
private:

    double val;

public:

    /** \param val Връщаната стойност, еднаква за всички аргументи на функцията
     */
    Constant(const double &val);
    virtual ~Constant();
    virtual double value(const std::map<std::string, double> &params) const override;
};

}; //end namespace

#endif
