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

    fret_t val;

protected:

    virtual fret_t value(const fparams_t& params) const override;
    virtual std::string toStringImpl() const override;

public:

    /** \param val Връщаната стойност, еднаква за всички аргументи на функцията
     */
    Constant(const fret_t& val);
    virtual ~Constant();
    fvariables_t variables() const override;
};

}; //end namespace

#endif
