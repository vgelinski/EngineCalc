#include <chrono>
#include <iostream>
#include <stdio.h>

#include "math/constant.h"
#include "math/identity.h"
#include "util/plot/plot_builder_2d.h"

#define SU SimpleUnit
#define CU CompoundUnit

using namespace std;
using namespace std::chrono;
using namespace engc::math;
using namespace engc::physics;
using namespace engc::util;

void calculation() {
    shared_ptr<CU> km = make_shared<CU>(SU::KiloMeters);
    shared_ptr<CU> h = make_shared<CU>(SU::Hours);
    shared_ptr<CU> kmPh = km / h;

    shared_ptr<CU> g = make_shared<CU>(SU::Grams);

    shared_ptr<CU> min = make_shared<CU>(SU::Minutes);

    auto acc = 0.5; // m/s^2
    auto speedF = make_shared<Constant>(acc) * make_shared<Identity>("t");//m/s

    auto mass = 0.1; //kg
    auto massF = make_shared<Identity>("m");

    auto energyF = massF * speedF * speedF / make_shared<Constant>(2);
    auto j = (kmPh * kmPh * g)->siUnit();

    auto start = make_shared<Value>(0, min);
    auto end = make_shared<Value>(20, min);
    auto step = make_shared<Value>(1, min);

    fparams_t p;
    p["m"] = mass;

    make_shared<PlotBuilder2D>()
            ->addLine(speedF, kmPh, "speed")
            ->addLine(massF, g, "mass")
            ->addLine(energyF, j, "Energy")
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

    cout << duration << endl;
    return 0;
}
