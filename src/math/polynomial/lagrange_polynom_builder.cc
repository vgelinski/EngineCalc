#include "lagrange_polynom_builder.h"

using namespace std;
using namespace engc::math;

#define LPB LagrangePolynomBuilder

LPB::LPB(const string& param) : param(param) {}
LPB::~LPB() {}

void LPB::addPoint(const fret_t& x, const fret_t& y) {
    points.push_back(pair(x, y));
}

shared_ptr<Polynomial> LPB::build() const {
    auto ret = make_shared<Polynomial>();
    for (size_t i = 0; i < points.size(); i++) {
        ret = ret->add(l_i(i)->multiply(y_i(i)));
    }
    return ret;
}

fret_t LPB::x_i(const size_t& i) const {
    return points[i].first;
}

fret_t LPB::y_i(const size_t& i) const {
    return points[i].second;
}

shared_ptr<Polynomial> LPB::l_i(const size_t& i) const {
    auto ret = make_shared<Polynomial>();
    for (size_t j = 0; j < points.size(); j++) {
        if (j == i) { continue; }
        auto tmp = make_shared<Polynomial>();
        tmp->add(make_shared<Monomial>(param, 1, 1 / (x_i(i) - x_i(j))));
        tmp->add(make_shared<Monomial>( - x_i(j) / (x_i(i) - x_i(j))));
        ret = ret->multiply(tmp);
    }
    return ret;
}
