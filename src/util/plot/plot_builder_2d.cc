#include "plot_builder_2d.h"

#define PB PlotBuilder2D

using namespace std;
using namespace engc::math;
using namespace engc::physics;
using namespace engc::util;

PB::PB() : filename("plot.csv"), separator(';') {}

PB::~PB() {}


shared_ptr<PlotBuilder2D> PB::setFilename(const std::string& filename) {
    this->filename = filename;
    return shared_from_this();
}

shared_ptr<PlotBuilder2D> PB::setSeparator(const char& separator) {
    this->separator = separator;
    return shared_from_this();
}

shared_ptr<PlotBuilder2D> PB::setStart(const valuePtr_t& start) {
    this->start = start;
    return shared_from_this();
}

shared_ptr<PlotBuilder2D> PB::setEnd(const valuePtr_t& end) {
    this->end = end;
    return shared_from_this();
}

shared_ptr<PlotBuilder2D> PB::setStep(const valuePtr_t& step) {
    this->step = step;
    return shared_from_this();
}

shared_ptr<PlotBuilder2D> PB::setParams(const math::fparams_t& params) {
    this->params = params;
    return shared_from_this();
}

shared_ptr<PlotBuilder2D> PB::setParamToPlot(const std::string& paramToPlot) {
    this->paramToPlot = paramToPlot;
    return shared_from_this();
}

shared_ptr<PlotBuilder2D> PB::addLine(
        const std::shared_ptr<Function>& f,
        const std::shared_ptr<CompoundUnit>& unit,
        const std::string& lineName) {

    lines.push_back(pair(f, unit));
    lineNames.push_back(lineName);
    return shared_from_this();
}

shared_ptr<Simple2DPlotter> PB::build() const {
    auto dataCalc = make_shared<DataCalculator2D>(lines, start, end, step, params, paramToPlot);
    return make_shared<Simple2DPlotter>(filename, separator, dataCalc, lineNames);
}