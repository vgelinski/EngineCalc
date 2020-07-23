#include "function.h"

#include <algorithm>

#include "differential.h"
#include "identity.h"
#include "integral.h"

using namespace std;
using namespace engc::math;

Function::~Function() {}

fret_t Function::operator()(const fparams_t& params) const {
    return value(params); //TODO optimize
}

shared_ptr<Function> Function::compose(
        const shared_ptr<Function> other, const string& paramName) const {

    return make_shared<Composition>(shared_from_this(), other, paramName);
}

shared_ptr<const Function> Function::substitute(
        const string& oldName, const string& newName) const {

    //TODO use contains after migrating to C++20
    if (variables().count(oldName) == 0) {
        return shared_from_this();
    }

    return compose(make_shared<Identity>(newName), oldName);
}

shared_ptr<Function> Function::integrate(
        fret_t start, fret_t end,
        const string& paramName,
        fret_t errBound) const {

    return IntegralCalculator::integrate(shared_from_this(), start, end, paramName, errBound);
}

shared_ptr<Function> Function::derive(const std::string& paramName, engc::math::fret_t errBound) const {
    return DifferentialCalculator::derive(shared_from_this(), paramName, errBound);
}

Function::Aggregation::Aggregation(
		const shared_ptr<Function>& f1,
		const operator_t& op,
		const shared_ptr<Function>& f2
		) : f1(f1), f2(f2), op(op){}

Function::Aggregation::~Aggregation() {}

fret_t Function::Aggregation::value(const fparams_t& p) const {
    return op(f1->value(p), f2->value(p));
}

fvariables_t Function::Aggregation::variables() const {
    fvariables_t ret;
    set_union(
        f1->variables().begin(), f1->variables().end(),
        f2->variables().begin(), f2->variables().end(),
        inserter(ret, ret.begin())
    );
    return ret;
}

Function::Composition::Composition(
        const shared_ptr<const Function> superF,
        const shared_ptr<const Function> subF,
        const string& paramName
    ) : superF(superF), subF(subF), paramName(paramName){}

Function::Composition::~Composition(){}

fret_t Function::Composition::value(const fparams_t& params) const {
    fparams_t mParams = params;
    mParams[paramName] = subF->value(params);
    return superF->value(mParams);
}

fvariables_t Function::Composition::variables() const {
    fvariables_t p1 = superF->variables();
    p1.erase(paramName);
    fvariables_t ret;
    set_union(
        p1.begin(), p1.end(),
        subF->variables().begin(), subF->variables().end(),
        inserter(ret, ret.begin())
    );
    return ret;
}

shared_ptr<Function> engc::math::operator+(const shared_ptr<Function> lhs, const shared_ptr<Function> rhs) {
	return make_shared<Function::Aggregation>(
			lhs,
			[](const fret_t& a, const fret_t& b) {return a + b;},
			rhs);
}


shared_ptr<Function> engc::math::operator-(const shared_ptr<Function> lhs, const shared_ptr<Function> rhs) {
	return make_shared<Function::Aggregation>(
			lhs,
			[](const fret_t& a, const fret_t& b) {return a - b;},
			rhs);
}

shared_ptr<Function> engc::math::operator*(const shared_ptr<Function> lhs, const shared_ptr<Function> rhs) {
	return make_shared<Function::Aggregation>(
			lhs,
			[](const fret_t& a, const fret_t& b) {return a * b;},
			rhs);
}

shared_ptr<Function> engc::math::operator/(const shared_ptr<Function> lhs, const shared_ptr<Function> rhs) {
	return make_shared<Function::Aggregation>(
			lhs,
			[](const fret_t& a, const fret_t& b) {return a / b;},
			rhs);
}

