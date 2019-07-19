#include "units.h"

#include <cmath>
#include <numeric>
#include <set>

using namespace engc::physics;
using namespace std;

#define SUT SimpleUnitType
#define SU SimpleUnit
#define CU CompoundUnit

const vector<SU const *>& SU::values() {
    return SU::vals;
}

SU::SU(
        const long double& multiplier,
        const SUT type,
        const string& name)
        : multiplier(multiplier), type(type), name(name) {
    SU::vals.push_back(this);
}

SU::~SU() {}

const SU * const SU::siUnit() const {
    for (auto u : vals) {
        if (u->multiplier == 1 && u->type == type) return u;
    }
    return nullptr;
}

string SU::toString() const {return name;}

CU::CU(
        const std::unordered_map<SU const *, long double>& units,
        const long double& multiplier,
        const uname_t& name
      ) : units(units), multiplier(multiplier), name(name) {}

CU::CU(const SU * const unit) : multiplier(1.0L) {
    units[unit] = 1;
}

CU::~CU() {}

long double CU::siMultiplier() const {
    long double mult = multiplier;
    for (auto p : units) {
        mult *= pow(p.first->multiplier, p.second);
    }
    return mult;
}

shared_ptr<CU> CU::siUnit() const {
    unordered_map<SimpleUnit const *, long double> siUnits; 
    for (auto p : units) {
        siUnits[p.first->siUnit()] += p.second;
    }
    return shared_ptr<CU>(new CU(siUnits));
}

bool CU::canBeConverted(const shared_ptr<CU>& o) const {
    return siUnit()->units == o->siUnit()->units;
}

string CU::toString() const {
    return name.value_or(toDebugString());
}

string CU::toDebugString() const {
    set<string> numerator, denominator;
    for (auto p: units) {
        string str = p.first->toString();
        int degree = fabs(p.second);
        if (degree > 1) {
            str.append(string("^") + to_string(degree));
        }
        auto &toAppend = p.second >= 0.0L ? numerator : denominator;
        toAppend.insert(str);
    }
    auto appendF = [](const string &s1, const string &s2){
        return s1 + string("*") + s2;
    };
    string result =  accumulate(
            ++(numerator.begin()),
            numerator.end(),
            *numerator.begin(),
            appendF
    );
    if (!denominator.empty()) {
        result = accumulate(
                ++(denominator.begin()),
                denominator.end(),
                result + "/" + *denominator.begin(),
                appendF
        );
    }
    if (multiplier != 1.0L) {
        result = to_string(multiplier) + "*" + result;
    }
    return result;
}

string CU::toLatexString() const {return "";}

shared_ptr<CU> engc::physics::operator*(
        const shared_ptr<CU> lhs, const shared_ptr<CU> rhs) {

    unordered_map<SU const *, long double> mergedMap = lhs->units;
    for (auto p: rhs->units) {
        mergedMap[p.first] += p.second;
    }
    auto mult = lhs->multiplier * rhs->multiplier;
    return shared_ptr<CU>(new CU(mergedMap, mult));
}

shared_ptr<CU> engc::physics::operator/(
        const shared_ptr<CU> lhs, const shared_ptr<CU> rhs) {

    unordered_map<SU const *, long double> mergedMap = lhs->units;
    for (auto p: rhs->units) {
        mergedMap[p.first] -= p.second;
    }
    auto mult = lhs->multiplier / rhs->multiplier;
    return shared_ptr<CU>(new CU(mergedMap, mult));
}
