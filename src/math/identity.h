#ifndef IDENTITY_H
#define IDENTITY_H

#include "function.h"

#include <string>
#include <map>

namespace engc::math {

/** \brief Клас, моделиращ идентитет.
 *
 */
class Identity : public Function {
private:

    std::string paramName;

protected:

    virtual double value(const fparams_t &params) const override;

public:

    /** \param paramName Името на параметъра, по който е идентитетът.
     */
    Identity(const std::string &paramName);
    virtual ~Identity();

    fvariables_t variables() const override;
};

}; //end namespace

#endif
