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

protected:

    virtual double value(const fparams_t &params) const override;

public:

    /** \param val Връщаната стойност, еднаква за всички аргументи на функцията
     */
    Constant(const double &val);
    virtual ~Constant();
};

}; //end namespace

#endif
