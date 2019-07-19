#include <chrono>
#include <iostream>
#include <stdio.h>

#include "math/constant.h"
#include "math/identity.h"
#include "physics/common_units.h"
#include "util/plot/plot_builder_2d.h"

#define SU SimpleUnit
#define CU CompoundUnit

using namespace std;
using namespace std::chrono;
using namespace engc::math;
using namespace engc::physics;
using namespace engc::util;

void calculation() {
    auto acc = 0.5; // m/s^2
    auto speedF = make_shared<Constant>(acc) * make_shared<Identity>("t");//m/s

    auto mass = 0.1; //kg
    auto massF = make_shared<Identity>("m");

    auto energyF = massF * speedF * speedF / make_shared<Constant>(2);

    auto start = make_shared<Value>(0, CommonUnits::Time::min);
    auto end = make_shared<Value>(20, CommonUnits::Time::min);
    auto step = make_shared<Value>(1, CommonUnits::Time::min);

    fparams_t p;
    p["m"] = mass;

    make_shared<PlotBuilder2D>()
            ->setFilename("plot/sandbox.csv")
            ->addLine(speedF, CommonUnits::Speed::KmPh, "speed")
            ->addLine(massF, CommonUnits::Mass::g, "mass")
            ->addLine(energyF, CommonUnits::Energy::KJ, "Energy")
            ->setStart(start)
            ->setEnd(end)
            ->setStep(step)
            ->setParams(p)
            ->setParamToPlot("t")
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
