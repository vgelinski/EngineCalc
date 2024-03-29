#include "simple_2d_plotter.h"

#include <numeric>

#include "../files/file_io.h"

#define DC DataCalculator2D
#define S2DP Simple2DPlotter

using namespace std;
using namespace engc::physics;
using namespace engc::util;

S2DP::S2DP(
        const std::string& filename,
        const char& separator,
        const shared_ptr<DataCalculator2D>& dataCalc,
        const std::vector<std::string>& lineNames,
        const std::string& paramToPlot
) : filename(filename),
        separator(separator),
        dataCalc(dataCalc),
        lineNames(lineNames),
        paramToPlot(paramToPlot) {}

S2DP::~S2DP() {}

void S2DP::plot() {
    auto plotContent = accumulate(
            lineNames.begin(),
            lineNames.end(),
            paramToPlot,
            [this](const string& a, const string& b) -> string {
                return a + string(1, separator) + "\t" + b;
            }
     );
    plotContent += "\n";
    for (auto row : dataCalc->calculateData()) {
        plotContent += std::accumulate(
                row.begin(),
                row.end(),
                string(),
                [this](const string& a, const shared_ptr<Value>& b) -> string {
                    return a + (a.length() > 0 ? string(1, separator) + "\t" : "") + to_string(b->value);
                }
        );
        plotContent += "\n";
    }
    FileIO::writeToFile(filename, plotContent);
}


