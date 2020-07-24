#include "monomial.h"

using namespace std;
using namespace engc::math;

Monomial::Monomial() : powers(), multiplier(1.0L) {}
Monomial::~Monomial() {}

fret_t Monomial::value(const fparams_t& params) const {
    return 0.0L;
}

fvariables_t Monomial::variables() const {
    return fvariables_t({});
}

void Monomial::setMultiplier(const fret_t& multiplier) {

}

void Monomial::addVariable(const std::string& name, const uint_fast8_t& power) {

}
