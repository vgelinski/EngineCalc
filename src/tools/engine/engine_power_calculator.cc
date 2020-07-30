#include "engine_power_calculator.h"

#include "../../math/constant.h"
#include "../../math/identity.h"
#include "../../math/max_function.h"
#include "../../model/engine/common_engines.h"
#include "../../model/transmission/common_differentials.h"
#include "../../model/transmission/common_gearboxes.h"
#include "../../model/transmission/transmission.h"
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

    auto engine1 = CommonEngines::VAZ::VAZ_2103();
    auto momentumF1 = engine1->precalculatedMomentumF;
    auto powerF1 = engine1->precalculatedPowerF;

    auto engine2 = CommonEngines::VAZ::VAZ_2106();
    auto momentumF2 = engine2->precalculatedMomentumF;
    auto powerF2 = engine2->precalculatedPowerF;

    auto start = make_shared<Value>(0, CommonUnits::Speed::rpm);
    auto end = make_shared<Value>(8000, CommonUnits::Speed::rpm);
    auto step = make_shared<Value>(100, CommonUnits::Speed::rpm);

    fparams_t p;

    make_shared<PlotBuilder2D>()
            ->setFilename("plot/engine_momentum_power_by_rpm/data.csv")
            ->addLine(momentumF1, CommonUnits::Torque::Nm, "momentum1")
            ->addLine(powerF1, CommonUnits::Power::HP, "power1")
            ->addLine(momentumF2, CommonUnits::Torque::Nm, "momentum2")
            ->addLine(powerF2, CommonUnits::Power::HP, "power2")
            ->setStart(start)
            ->setEnd(end)
            ->setStep(step)
            ->setParams(p)
            ->setParamToPlot("rotationSpeed")
            ->build()
            ->plot();
}

void EPC::plotPowerBySpeed() {

    auto engine1 = CommonEngines::VAZ::VAZ_2106();
    auto powerF1 = engine1->precalculatedPowerF;
    auto tyre1 = make_shared<Tyre>(185, 80, 13);
    auto transmission1 = make_shared<Transmission>(
            tyre1,
            tyre1,
            CommonDifferentials::VAZ::VAZ_2103(),
            CommonGearboxes::VAZ::VAZ_2105()
    );
    auto maxF1 = make_shared<MaxFunction>();

    for (int i = 1; i <= 5; i++) {
        transmission1->gearbox->shiftToGear(i);
        maxF1->addFunction(powerF1->compose(transmission1->rotationF(), "rotationSpeed"));
    }

    auto engine2 = CommonEngines::VAZ::VAZ_2106();
    auto powerF2 = engine2->precalculatedPowerF;
    auto tyre2 = make_shared<Tyre>(185, 80, 13);
    auto transmission2 = make_shared<Transmission>(
            tyre2,
            tyre2,
            CommonDifferentials::VAZ::VAZ_2102(),
            CommonGearboxes::VAZ::R1()
    );
    auto maxF2 = make_shared<MaxFunction>();

    for (int i = 1; i <= 5; i++) {
        transmission2->gearbox->shiftToGear(i);
        maxF2->addFunction(powerF2->compose(transmission2->rotationF(), "rotationSpeed"));
    }

    auto start = make_shared<Value>(0, CommonUnits::Speed::KmPh);
    auto end = make_shared<Value>(250, CommonUnits::Speed::KmPh);
    auto step = make_shared<Value>(1, CommonUnits::Speed::KmPh);

    fparams_t p;

    make_shared<PlotBuilder2D>()
            ->setFilename("plot/engine_power_by_speed/data.csv")
            ->addLine(maxF1, CommonUnits::Power::HP, "power1")
            ->addLine(maxF2, CommonUnits::Power::HP, "power2")
            ->setStart(start)
            ->setEnd(end)
            ->setStep(step)
            ->setParams(p)
            ->setParamToPlot("speed")
            ->build()
            ->plot();
}
