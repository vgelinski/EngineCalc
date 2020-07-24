#ifndef ENGINECALC_MONOMIAL_H
#define ENGINECALC_MONOMIAL_H

#include "../function.h"

namespace engc::math {
class Monomial : public Function {
private:
    std::unordered_map<std::string, uint_fast8_t> powers;
    fret_t multiplier;

protected:
    virtual fret_t value(const fparams_t& params) const override;

public:
    Monomial();
    virtual ~Monomial();

    virtual fvariables_t variables() const override;

    virtual void setMultiplier(const fret_t& multiplier);
    virtual void addVariable(const std::string& name, const uint_fast8_t& power);
};
};


#endif //ENGINECALC_MONOMIAL_H
