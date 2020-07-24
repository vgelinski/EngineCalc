#include "monomial.h"

#include <numeric>
#include <cmath>

using namespace std;
using namespace engc::math;

Monomial::Monomial() : powers(), multiplier(1.0L) {}
Monomial::~Monomial() {}

fret_t Monomial::value(const fparams_t& params) const {
    return std::accumulate(
            powers.begin(),
            powers.end(),
            multiplier,
            [this, params](const fret_t& acc, const pair<string, uint_fast8_t>& entry) -> fret_t {
                return acc * pow(params.at(entry.first), entry.second);
            }
    );
}

fvariables_t Monomial::variables() const {
    return std::accumulate(
            powers.begin(),
            powers.end(),
            fvariables_t({}),
            [this](fvariables_t& acc, const pair<string, uint_fast8_t>& entry) -> fvariables_t {
                acc.insert(entry.first);
                return acc;
            }
    );
}

void Monomial::setMultiplier(const fret_t& multiplier) {
    this->multiplier = multiplier;
}

void Monomial::addVariable(const std::string& name, const uint_fast8_t& power) {
    powers[name] = power;
}
