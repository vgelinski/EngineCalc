#include "simple_2d_plotter.h"

#define DC DataCalculator2D
#define S2DP Simple2DPlotter

using namespace std;
using namespace engc::util;

S2DP::S2DP(
        const std::string& filename,
        const char& separator,
        const shared_ptr<DataCalculator2D>& dataCalc,
        const std::vector<std::string>& lineNames
    ) : filename(filename),
        separator(separator),
        dataCalc(dataCalc),
        lineNames(lineNames) {}

S2DP::~S2DP() {}

void S2DP::plot() {
}


