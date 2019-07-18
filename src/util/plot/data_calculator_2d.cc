#include "data_calculator_2d.h"

using namespace std;
using namespace engc::math;
using namespace engc::physics;
using namespace engc::util;

#define DC DataCalculator2D

DC::DC(
        const vector<line_t>& lines,
        const valuePtr_t& start,
        const valuePtr_t& end,
        const valuePtr_t& step,
        const fparams_t& params,
        const string& paramToPlot
    ) : 
        lines(lines),
         start(start),
         end(end),
         step(step),
         params(params),
         paramToPlot(paramToPlot) {}

DC::~DC() {}

vector<vector<valuePtr_t>> DC::calculateData() {
    auto siStart = start->convertToSi();
    auto siEnd = end->convertToSi();
    auto siStep = step->convertToSi();
    vector<vector<valuePtr_t>> result;
    for (fret_t i = siStart->value; i <= siEnd->value; i+= siStep->value) {
        result.push_back(calculateRow(i, siStart->unit));
    }
    return result;
}

vector<valuePtr_t> DC::calculateRow(
        const fret_t& currVal,
        const shared_ptr<CompoundUnit>& u) {

    vector<valuePtr_t> row{make_shared<Value>(currVal, u)->convertTo(start->unit)};
    for (auto line : lines) {
        const auto& f = *line.first;
        auto unit = line.second;
        params[paramToPlot] = currVal;
        auto y = f(params);
        auto siVal = make_shared<Value>(y, unit->siUnit());
        row.push_back(siVal->convertTo(unit));
    }
    return row;
}

