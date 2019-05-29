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

public:

    /** \param paramName Името на параметъра, по който е идентитетът.
     */
    Identity(const std::string &paramName);
    virtual ~Identity();
    virtual double value(const std::map<std::string, double> &params) const override;
};

}; //and namespace

#endif
