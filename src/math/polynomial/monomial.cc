#include "monomial.h"

#include <numeric>
#include <cmath>

using namespace std;
using namespace engc::math;

Monomial::Monomial() : powers(), multiplier(1.0L) {}
Monomial::Monomial(const string& name, const uint_fast8_t& power, const fret_t& multiplier) : Monomial() {
    addVariable(name, power);
    setMultiplier(multiplier);
}
Monomial::Monomial(const fret_t& multiplier) : Monomial() {
    setMultiplier(multiplier);
}
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

string Monomial::toStringImpl() const {
    char buffer[1024];
    sprintf(buffer, "%Lg", multiplier);
    auto ret = string(buffer);
    return (multiplier > 0 && powers.size() == 0 ? "" : "\\left(" )
            + std::accumulate(
                    powers.begin(),
                    powers.end(),
                    ret,
                    [](const string& acc, const pair<string, uint_fast8_t>& entry) -> string {
                        auto power = entry.second;
                        auto powerStr = power == 1 ?
                                        "" :
                                        (power < 10 ? "^" + to_string(power) : "^{" + to_string(power) + "}");
                        return acc + (entry.first + powerStr);
                    }
            )
            + (multiplier > 0 && powers.size() == 0 ? "" : "\\right)" );
};

fvariables_t Monomial::variables() const {
    fvariables_t ret;
    std::transform(
            powers.begin(),
            powers.end(),
            std::inserter(ret, ret.end()),
            [](const pair<string, uint_fast8_t>& entry) -> string {
                return entry.first;
            }
    );
    return ret;
}

const unordered_map<string, uint_fast8_t>& Monomial::getPowers() const {
    return powers;
}

void Monomial::setPowers(const unordered_map<string, uint_fast8_t>& powers) {
    this->powers = powers;
}

void Monomial::setMultiplier(const fret_t& multiplier) {
    this->multiplier = multiplier;
}

fret_t Monomial::getMultiplier() const {
    return multiplier;
}

void Monomial::addVariable(const std::string& name, const uint_fast8_t& power) {
    if (power != 0) {
        powers[name] += power;
    }
}


shared_ptr<Monomial> Monomial::multiply(const shared_ptr<const Monomial>& other) const {
    unordered_map<string, uint_fast8_t> pwrs = this->getPowers();
    auto f = [&pwrs](const pair<string, uint_fast8_t>& entry) -> void { pwrs[entry.first] += entry.second; };
    for_each(
            other->getPowers().begin(),
            other->getPowers().end(),
            f
    );
    auto mon = make_shared<Monomial>();
    mon->setPowers(pwrs);
    mon->setMultiplier(other->getMultiplier() * multiplier);
    return mon;
}
