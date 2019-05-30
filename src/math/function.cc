#include "function.h"

using namespace std;
using namespace engc::math;

Function::~Function() {}

double Function::operator()(const fparams_t &params) const {
    return value(params); //TODO optimize
}

shared_ptr<Function> Function::compose(
        const shared_ptr<Function> other, const string &paramName) const {

    return make_shared<Composition>(shared_from_this(), other, paramName);
}

Function::Aggregation::Aggregation(
		const shared_ptr<Function> &f1,
		const operator_t &op,
		const shared_ptr<Function> &f2
		) : f1(f1), f2(f2), op(op){}

Function::Aggregation::~Aggregation() {}

double Function::Aggregation::value(const map<string, double> &p) const {
    return op(f1->value(p), f2->value(p));
}

Function::Composition::Composition(
        const shared_ptr<const Function> superF,
        const shared_ptr<const Function> subF,
        const string &paramName
    ) : superF(superF), subF(subF), paramName(paramName){}

Function::Composition::~Composition(){}

double Function::Composition::value(const map<string, double> &params) const {
    map<string, double> mParams = params;
    mParams[paramName] = subF->value(params);
    return superF->value(mParams);
}


shared_ptr<Function> engc::math::operator+(const shared_ptr<Function> lhs, const shared_ptr<Function> rhs) {
	return make_shared<Function::Aggregation>(
			lhs,
			[](const double &a, const double &b) {return a + b;},
			rhs);
}


shared_ptr<Function> engc::math::operator-(const shared_ptr<Function> lhs, const shared_ptr<Function> rhs) {
	return make_shared<Function::Aggregation>(
			lhs,
			[](const double &a, const double &b) {return a - b;},
			rhs);
}

shared_ptr<Function> engc::math::operator*(const shared_ptr<Function> lhs, const shared_ptr<Function> rhs) {
	return make_shared<Function::Aggregation>(
			lhs,
			[](const double &a, const double &b) {return a * b;},
			rhs);
}

shared_ptr<Function> engc::math::operator/(const shared_ptr<Function> lhs, const shared_ptr<Function> rhs) {
	return make_shared<Function::Aggregation>(
			lhs,
			[](const double &a, const double &b) {return a / b;},
			rhs);
}

