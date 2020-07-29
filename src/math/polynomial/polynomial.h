#ifndef ENGINECALC_POLYNOMIAL_H
#define ENGINECALC_POLYNOMIAL_H

#include "monomial.h"

#include <list>

namespace engc::math {
class Polynomial : public Function {
public:
    struct Hash{
        std::size_t operator()(const std::unordered_map<std::string, uint_fast8_t>& k) const;
    };
private:
    std::unordered_map<std::unordered_map<std::string, uint_fast8_t>, std::shared_ptr<const Monomial>, Hash> monomials;

protected:
    virtual fret_t value(const fparams_t& params) const override;

public:
    Polynomial();
    virtual ~Polynomial();

    virtual fvariables_t variables() const override;

    virtual void add(std::shared_ptr<Monomial> monomial);

private:

    virtual std::list<std::shared_ptr<const Monomial>> getMonomials() const;

};
};


#endif //ENGINECALC_POLYNOMIAL_H
