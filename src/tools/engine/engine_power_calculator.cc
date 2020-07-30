#include "engine_power_calculator.h"

#include "../../math/constant.h"
#include "../../math/identity.h"
#include "../../model/engine/common_engines.h"
#include "../../physics/common_units.h"
#include "../../util/plot/plot_builder_2d.h"

using namespace std;
using namespace engc::tools;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;
using namespace engc::util;

#define EPC EnginePowerCalculator

#define SU SimpleUnit
#define CU CompoundUnit

void EPC::plotPowerByRodLength() {

    auto engine = CommonEngines::VAZ::VAZ_2101();
    auto lossF= engine->mechanicalLossF();

    auto start = engine->getRodLength();
    auto end = make_shared<Value>(start->convertTo(CommonUnits::Length::mm)->value + 200, CommonUnits::Length::mm);
    auto step = make_shared<Value>(10, CommonUnits::Length::mm);

    fparams_t p = engine->getParams();
    p["rotationSpeed"] = make_shared<Value>(5600, CommonUnits::Speed::rpm)->convertToSi()->value;

    make_shared<PlotBuilder2D>()
            ->setFilename("plot/sandbox.csv")
            ->addLine(lossF, CommonUnits::Power::HP, "phi")
            ->setStart(start)
            ->setEnd(end)
            ->setStep(step)
            ->setParams(p)
            ->setParamToPlot("rodLength")
            ->build()
            ->plot();
}

void EPC::plotMomentumAndPower() {

    auto engine = CommonEngines::VAZ::VAZ_2105();
    auto momentumF = engine->precalculatedMomentumF;
    auto powerF = engine->precalculatedPowerF;

    auto start = make_shared<Value>(0, CommonUnits::Speed::rpm);
    auto end = make_shared<Value>(8000, CommonUnits::Speed::rpm);
    auto step = make_shared<Value>(100, CommonUnits::Speed::rpm);

    fparams_t p = engine->getParams();

    make_shared<PlotBuilder2D>()
            ->setFilename("plot/engine_momentum_power_by_rpm/data.csv")
            ->addLine(momentumF, CommonUnits::Torque::Nm, "momentum")
            ->addLine(powerF, CommonUnits::Power::HP, "power")
            ->setStart(start)
            ->setEnd(end)
            ->setStep(step)
            ->setParams(p)
            ->setParamToPlot("rotationSpeed")
            ->build()
            ->plot();
}
