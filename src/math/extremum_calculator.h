#ifndef EXTREMUM_CALCULATOR_H
#define EXTREMUM_CALCULATOR_H

#include "function/function.h"

namespace engc::math {

class ExtremumCalculator {
private:

    typedef std::pair<fret_t, fret_t> pbound_t;

    const std::shared_ptr<Function> function;
    fparams_t params;
    const fret_t errBound;

    std::unordered_map<std::string, pbound_t> paramBoundsMap;
    std::vector<std::pair<std::string, pbound_t>> paramBoundsList;
    fret_t minV, maxV;
    fparams_t minP, maxP;

    void solveFor(const std::size_t& pos);

public:
    ExtremumCalculator(const std::shared_ptr<Function>& f, const fparams_t& params, const fret_t& errBound = 0.0000001);
    virtual ~ExtremumCalculator();

    void setParamBound(const std::string& pName, const fret_t& start, const fret_t& end);
    void calculate();

    fret_t minVal() const;
    fret_t maxVal() const;
    fparams_t minAt() const;
    fparams_t maxAt() const;
};
};

#endif //EXTREMUM_CALCULATOR_H
