#include <chrono>
#include <iostream>
#include <stdio.h>

#include "math/constant.h"
#include "math/identity.h"
#include "model/engine/common_engines.h"
#include "physics/common_units.h"
#include "util/plot/plot_builder_2d.h"

#define SU SimpleUnit
#define CU CompoundUnit

using namespace std;
using namespace std::chrono;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;
using namespace engc::util;

void calculation() {
    auto vaz2101 = CommonEngines::VAZ::VAZ_2101();
    auto lossF= vaz2101->mechanicalLossF();

    auto start = vaz2101->getRodLength();
    auto end = make_shared<Value>(start->convertTo(CommonUnits::Length::mm)->value + 200, CommonUnits::Length::mm);
    auto step = make_shared<Value>(10, CommonUnits::Length::mm);

    fparams_t p = vaz2101->getParams();
    p["rotationSped"] = make_shared<Value>(5600, CommonUnits::Speed::rpm)->convertToSi()->value;

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

int main() {
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    calculation();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    cout <<  "The execution took " << duration << "ms" << endl;
    return 0;
}
