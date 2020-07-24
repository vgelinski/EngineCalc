#ifndef ENGINECALC_POLYNOMIAL_H
#define ENGINECALC_POLYNOMIAL_H

#include "monomial.h"

namespace engc::math {
class Polynomial : public Function {
private:
    std::unordered_set<std::shared_ptr<Monomial>> monomials;

protected:
    virtual fret_t value(const fparams_t& params) const override;

public:
    Polynomial();
    virtual ~Polynomial();

    virtual fvariables_t variables() const override;

    virtual void addMonomial(std::shared_ptr<Monomial>);

};
};


#endif //ENGINECALC_POLYNOMIAL_H
