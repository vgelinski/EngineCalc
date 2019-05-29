#include "function.h"

using namespace std;
using namespace engc::math;

Function::~Function() {}

Function::Aggregation::Aggregation(
		const shared_ptr<Function> &f1,
		const operator_t &op,
		const shared_ptr<Function> &f2
		) {
	this->f1 = f1;
	this->f2 = f2;
	this->op = op;
}

Function::Aggregation::~Aggregation() {}

double Function::Aggregation::value(const map<string, double> &p) const {
    return op(f1->value(p), f2->value(p));
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

