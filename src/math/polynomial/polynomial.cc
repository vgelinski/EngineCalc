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

string Polynomial::toStringImpl() const {
    auto monos = getMonomials();
    string acc = "\\left(";
    std::accumulate(
            monos.begin(),
            monos.end(),
            0,
            [&acc](int index, const shared_ptr<const Monomial>& monomial) -> int {
                if (index == 0) {
                    acc.append(monomial->toString());
                } else {
                    acc.append(" + " + monomial->toString());
                }
                return index + 1;
            }
    );
    acc.append("\\right)");
    return acc;
};

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

void Polynomial::add(shared_ptr<const Monomial> monomial) {
    auto pwrs = monomial->getPowers();
    auto currMonom = monomials[pwrs];
    auto multiplier = monomial->getMultiplier()
                      + (currMonom == nullptr ? 0.0L : currMonom->getMultiplier());
    auto newMonom = make_shared<Monomial>();
    newMonom->setPowers(pwrs);
    newMonom->setMultiplier(multiplier);
    monomials[pwrs] = newMonom;
}

shared_ptr<Polynomial> Polynomial::add(shared_ptr<const Polynomial> other) const {
    auto monomsOther = other->getMonomials();
    auto monomsThis = this->getMonomials();
    monomsOther.splice(monomsOther.end(), monomsThis);
    auto ret = make_shared<Polynomial>();
    for_each(
            monomsOther.begin(),
            monomsOther.end(),
            [ret](const shared_ptr<const Monomial>& monom) -> void {
                ret->add(monom);
            }
    );
    return ret;
}

shared_ptr<Polynomial> Polynomial::multiply(shared_ptr<const Monomial> monomial) const {
    auto ret = make_shared<Polynomial>();
    ret->add(monomial);
    return multiply(ret);
}

shared_ptr<Polynomial> Polynomial::multiply(shared_ptr<const Polynomial> other) const {
    auto monomsthis = getMonomials();
    auto monomsOther = other->getMonomials();
    auto ret = make_shared<Polynomial>();
    for_each(
            monomsthis.begin(),
            monomsthis.end(),
            [this, monomsOther, ret](const shared_ptr<const Monomial>& monom1) -> void {
                for_each(
                        monomsOther.begin(),
                        monomsOther.end(),
                        [this, monom1, ret](const shared_ptr<const Monomial>& monom2) -> void {
                            ret->add(monom1->multiply(monom2));
                        }
                );
            }
    );
    return ret;
}

shared_ptr<Polynomial> Polynomial::multiply(const fret_t& m) const {
    auto monomsthis = getMonomials();
    auto ret = make_shared<Polynomial>();
    for_each(
            monomsthis.begin(),
            monomsthis.end(),
            [this, ret, m](const shared_ptr<const Monomial>& monom) -> void {
                ret->add(monom->multiply(make_shared<Monomial>(m)));
            }
    );
    return ret;
}

list<shared_ptr<const Monomial>> Polynomial::getMonomials() const {
    return std::accumulate(
            monomials.begin(),
            monomials.end(),
            list<shared_ptr<const Monomial>>(),
            [](list<shared_ptr<const Monomial>> acc, const pair<unordered_map<string, uint_fast8_t>, shared_ptr<const Monomial>>& entry) -> list<shared_ptr<const Monomial>> {
                acc.push_back(entry.second);
                return acc;
            }
    );
}
