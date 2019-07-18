#ifndef PLOT_BUILDER_2_D_H
#define PLOT_BUILDER_2_D_H

#include "simple_2d_plotter.h"

namespace engc::util {
class PlotBuilder2D : public std::enable_shared_from_this<PlotBuilder2D> {

private:

    std::string filename;
    char separator;
    std::vector<line_t> lines;
    valuePtr_t start, end, step;
    math::fparams_t params;
    std::string paramToPlot;
    std::vector<std::string> lineNames;

public:

    PlotBuilder2D();
    virtual ~PlotBuilder2D();

    virtual std::shared_ptr<PlotBuilder2D> setFilename(const std::string& filename);
    virtual std::shared_ptr<PlotBuilder2D> setSeparator(const char& separator);
    virtual std::shared_ptr<PlotBuilder2D> setStart(const valuePtr_t& start);
    virtual std::shared_ptr<PlotBuilder2D> setEnd(const valuePtr_t& end);
    virtual std::shared_ptr<PlotBuilder2D> setStep(const valuePtr_t& step);
    virtual std::shared_ptr<PlotBuilder2D> setParams(const math::fparams_t& params);
    virtual std::shared_ptr<PlotBuilder2D> setParamToPlot(const std::string& paramToPlot);
    virtual std::shared_ptr<PlotBuilder2D> addLine(
            const std::shared_ptr<math::Function>& f,
            const std::shared_ptr<physics::CompoundUnit>& unit,
            const std::string& lineName
     );

    virtual std::shared_ptr<Simple2DPlotter> build() const;


};
}; //end namespace
#endif //PLOT_BUILDER_2_D_H
