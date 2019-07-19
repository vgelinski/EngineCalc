#ifndef SIMPLE_2D_PLOTTER_H
#define SIMPLE_2D_PLOTTER_H

#include "data_calculator_2d.h"

namespace engc::util {

class Simple2DPlotter {
private:

    const std::string filename;
    const char separator;
    std::shared_ptr<DataCalculator2D> dataCalc;
    const std::vector<std::string> lineNames;
    const std::string paramToPlot;

public:

    Simple2DPlotter(
        const std::string& filename,
        const char& separator,
        const std::shared_ptr<DataCalculator2D>& dataCalc,
        const std::vector<std::string>& lineNames,
        const std::string& paramToPlot
    );
    virtual ~Simple2DPlotter();

    virtual void plot();
};
}; //end namespace
#endif
