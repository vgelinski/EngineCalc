#ifndef ENGINECALC_LAGRANGE_POLYNOM_BUILDER_H
#define ENGINECALC_LAGRANGE_POLYNOM_BUILDER_H

#include "polynomial.h"

namespace engc::math {
class LagrangePolynomBuilder : public std::enable_shared_from_this<LagrangePolynomBuilder> {
private:
    std::vector<std::pair<fret_t, fret_t>> points;
    const std::string param;

public:



    /** \brief Клас, служещ за създаване на Полином на Лагранж
    *
    * Полиномът на Лагранж има следния вид: \f$L(x) = \sum_{i=0}^n y_i l_i(x\f$
    * Където базисните полиноми имат вида \f$l_i(x)=\prod_{j=0, j\neq i}^{n} \frac{x-x_j}{x_i-x_j} = \frac{x-x_0}{x_i-x_0} \cdots \frac{x-x_{i-1}}{x_i-x_{i-1}} \cdot \frac{x-x_{i+1}}{x_i-x_{i+1}} \cdots \frac{x-x_{n}}{x_i-x_{n}}\f$
    */
    LagrangePolynomBuilder(const std::string& param);
    virtual ~LagrangePolynomBuilder();

    virtual std::shared_ptr<LagrangePolynomBuilder> addPoint(const fret_t& x, const fret_t& y);
    virtual std::shared_ptr<Polynomial> build() const;

private:

    virtual fret_t x_i(const size_t& i) const;
    virtual fret_t y_i(const size_t& i) const;

    virtual std::shared_ptr<Polynomial> l_i(const size_t& i) const;
};
};


#endif //ENGINECALC_LAGRANGE_POLYNOM_BUILDER_H
