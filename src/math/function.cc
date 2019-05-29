#include "function.h"

Function::~Function() {}

Function::Aggregation::Aggregation(
		const std::shared_ptr<Function> &f1,
		const operator_t &op,
		const std::shared_ptr<Function> &f2
		) {
	this->f1 = f1;
	this->f2 = f2;
	this->op = op;
}

Function::Aggregation::~Aggregation() {}

double Function::Aggregation::value(const std::map<std::string, double> &p) const {
    return op(f1->value(p), f2->value(p));
}
