#include "integral.h"

#include <cmath>
#include <future>
#include <vector>

#include "constant.h"

using namespace std;
using namespace engc::math;

#define IC IntegralCalculator
#define MTI Integral

shared_ptr<Function> IC::integrate(
        shared_ptr<const Function> f,
        fret_t start, fret_t end,
        const string& param,
        fret_t errBound,
        int threadCount) {

    if (fabs(start - end) < errBound / 2.0L) {
        return make_shared<Constant>(0);
    }
    fret_t a = min(start, end);
    fret_t b = max(start, end);
    auto intgr = make_shared<Integral>(f, a, b, param, errBound);
    return start < end ? intgr : (make_shared<Constant>(-1) * intgr);
}

IC::MTI::Integral(
        shared_ptr<const Function> f,
        fret_t start, fret_t end,
        const string& param,
        fret_t errBound) : 
            start(start), end(end), errBound(errBound),
            function(f), param(param) {}

IC::MTI::~Integral() {}

fret_t IC::MTI::value(const fparams_t& params) const {
    int n = (end - start) / errBound;
    fret_t result = calculateForN(n, params);
    fret_t newResult = calculateForN(n*2, params);
    while(fabs(result - newResult) > errBound / 2.0L) {
        result = newResult;
        n *= 2;
        newResult = calculateForN(n*2, params);
    }
    return result;
}

string IC::MTI::toStringImpl() const {
    char buffer[1024];
    sprintf(buffer, "%Lg", start);
    auto startStr = string(buffer);
    sprintf(buffer, "%Lg", end);
    auto endStr = string(buffer);
    return "\\int_{"
           + startStr
           + "}^{"
           + endStr
           + "}"
           + function->toString()
           + "\\,d"
           + param;
};

fvariables_t IC::MTI::variables() const {
    fvariables_t vars = function->variables();
    vars.erase(param);
    return vars;
}

fret_t IC::MTI::calculateForN(int n, fparams_t params) const {
    fret_t sum = 0;
    fret_t h = (end - start) / n;
    int oneIterN = n / THREAD_COUNT;
    vector<future<fret_t>> futures;
    for (int i = 0; i <= THREAD_COUNT; i++) {
        fret_t a = start + i * oneIterN * h;
        int thisIterN = min(oneIterN, n - i * oneIterN);
        auto future = async(launch::async, [this, a, h, thisIterN,& params](){
            fret_t lSum = 0;
            fparams_t lParams = params;
            for(int i = 0; i < thisIterN; i++) {
                fret_t xi = a + i * h;
                lParams[param] = xi;
                lSum += (*function)(lParams);
            }
            return lSum;
        });
        futures.push_back(std::move(future));
    }

    for (auto& fut: futures) {
        sum += fut.get();
    }
    auto f = [this,& params](const fret_t& p) {
        params[param] = p;
        return (*function)(params);
    };
    fret_t result = h * sum - h * (f(end) - f(start)) / 2;
    return result;
}

