#include "extremum_calculator.h"

#include <limits>

using namespace std;
using namespace engc::math;

#define EC ExtremumCalculator

EC::ExtremumCalculator(const shared_ptr <Function>& f, const fparams_t& params, const fret_t& errBound)
        : function(f), params(params), errBound(errBound), minV(numeric_limits<fret_t >::max()), maxV(numeric_limits<fret_t >::min()) {}
        
EC::~ExtremumCalculator() {}

void EC::setParamBound(const string& pName, const fret_t& start, const fret_t& end) {
    paramBoundsMap[pName] = pair(start, end);
}

void EC::solveFor(const std::size_t& pos) {
    if (pos == paramBoundsList.size()) {
        auto val = (*function)(params);
        if (val > maxV) {
            maxV = val;
            maxP = params;
        }
        if (val < minV) {
            minV = val;
            minP = params;
        }
    } else {
        auto curr =  paramBoundsList[pos];
        auto pName = curr.first;
        auto start = curr.second.first;
        auto end = curr.second.second;
        fret_t i;
        for (i = start; i <= end; i += errBound) {
            params[pName] = i;
            solveFor(pos + 1);
        }
    }

}

void EC::calculate() {
    paramBoundsMap.reserve(paramBoundsMap.size());
    for (auto p : paramBoundsMap) {
        paramBoundsList.push_back(p);
    }
    solveFor(0);
}

fret_t EC::minVal() const {
    return minV;
}

fret_t EC::maxVal() const {
    return maxV;
}

fparams_t EC::minAt() const {
    return minP;
}

fparams_t EC::maxAt() const {
    return maxP;
}
