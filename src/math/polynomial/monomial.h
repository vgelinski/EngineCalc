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
    Monomial(const std::string& name, const uint_fast8_t& power, const fret_t& multiplier = 1.0L);
    virtual ~Monomial();

    virtual fvariables_t variables() const override;

    virtual std::shared_ptr<Monomial> multiply(const std::shared_ptr<const Monomial>& other) const;

    virtual const std::unordered_map<std::string, uint_fast8_t>& getPowers() const;
    virtual void setPowers(const std::unordered_map<std::string, uint_fast8_t>& powers);

    virtual void setMultiplier(const fret_t& multiplier);
    virtual fret_t getMultiplier() const;
    virtual void addVariable(const std::string& name, const uint_fast8_t& power);
};
};


#endif //ENGINECALC_MONOMIAL_H
