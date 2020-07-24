#include "polynomial.h"

#include <numeric>

using namespace std;
using namespace engc::math;

Polynomial::Polynomial() : monomials() {}

Polynomial::~Polynomial() {}

fret_t Polynomial::value(const fparams_t& params) const {
    return 0;
}

fvariables_t Polynomial::variables() const {
    return fvariables_t({});
}

void Polynomial::addMonomial(shared_ptr<Monomial> monomial) {
    monomials.insert(monomial);
}