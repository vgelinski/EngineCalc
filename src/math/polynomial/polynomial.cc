#include "polynomial.h"

#include <numeric>

using namespace std;
using namespace engc::math;

size_t Polynomial::Hash::operator()(const unordered_map<string, uint_fast8_t>& key) const {
    return std::accumulate(
            key.begin(),
            key.end(),
            0,
            [](size_t acc, const pair<string, uint_fast8_t>& entry) -> size_t {
                return acc + std::hash<string>{}(entry.first) * entry.second;
            }
    );
}

Polynomial::Polynomial() : monomials() {}

Polynomial::~Polynomial() {}

fret_t Polynomial::value(const fparams_t& params) const {
    auto monos = getMonomials();
    return std::accumulate(
            monos.begin(),
            monos.end(),
            0.0L,
            [params](const fret_t& acc, const shared_ptr<const Monomial>& monomial) -> fret_t {
                return acc + (* monomial)(params);
            }
    );
}

fvariables_t Polynomial::variables() const {
    auto monos = getMonomials();
    return std::accumulate(
            monos.begin(),
            monos.end(),
            fvariables_t({}),
            [](const fvariables_t& acc, const shared_ptr<const Monomial>& monomial) -> fvariables_t {
                fvariables_t ret;
                auto vars = monomial->variables();
                set_union(
                        acc.begin(), acc.end(),
                        vars.begin(), vars.end(),
                        inserter(ret, ret.begin())
                );
                return ret;
            }
    );
}

void Polynomial::add(shared_ptr<Monomial> monomial) {
    auto currMonom = monomials[monomial->getPowers()];
    monomial->setMultiplier(
            monomial->getMultiplier()
            + (currMonom == nullptr ? 0.0L : currMonom->getMultiplier())
    );
    monomials[monomial->getPowers()] = monomial;
}

list<shared_ptr<const Monomial>> Polynomial::getMonomials() const {
    return std::accumulate(
            monomials.begin(),
            monomials.end(),
            list<shared_ptr<const Monomial>>(),
            [](list<shared_ptr<const Monomial>>& acc, const pair<unordered_map<string, uint_fast8_t>, shared_ptr<const Monomial>>& entry) -> list<shared_ptr<const Monomial>>& {
                acc.push_back(entry.second);
                return acc;
            }
    );
}
