#ifndef DATA_CALCULATOR_2D_H
#define DATA_CALCULATOR_2D_H

#include "../../math/function.h"
#include "../../physics/value.h"

namespace engc::util {

typedef std::shared_ptr<math::Function> functionPtr_t;
typedef std::shared_ptr<physics::CompoundUnit> unitPtr_t;
typedef std::pair<functionPtr_t, unitPtr_t> line_t;
typedef std::shared_ptr<physics::Value> valuePtr_t;

class DataCalculator2D {
private:

    std::vector<line_t> lines;
    valuePtr_t start, end, step;
    math::fparams_t params;
    const std::string paramToPlot;

public:

    DataCalculator2D(
        const std::vector<line_t>& lines,
        const valuePtr_t& start,
        const valuePtr_t& end,
        const valuePtr_t& step,
        const math::fparams_t& params,
        const std::string& paramToPlot
    );
    virtual ~DataCalculator2D();

    std::vector<std::vector<valuePtr_t>> calculateData();

private:

    std::vector<valuePtr_t> calculateRow(
        const math::fret_t& currVal,
        const std::shared_ptr<physics::CompoundUnit>& u
    );
};
}; //end namespace
#endif
