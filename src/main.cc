#include <chrono>
#include <iostream>
#include <stdio.h>

#include "tools/engine/engine_power_calculator.h"
#include "tools/suspension/suspension_calculator.h"

#include "model/transmission/common_differentials.h"
#include "model/transmission/common_gearboxes.h"
#include "model/transmission/transmission.h"
#include "physics/common_units.h"

using namespace std;
using namespace std::chrono;
using namespace engc::tools;
using namespace engc::math;
using namespace engc::model;
using namespace engc::physics;

static const int EXIT = 0;
static const int PLOT_ENGINE_POWER_BY_ROD_LENGTH = 1;
static const int CALCULATE_OPTIMUM_REAR_SUSPENSION_BAR_LENGTHS = 2;
static const int CALCULATE_SPEED = 3;
static const int PLOT_MOMENTUM_AND_POWER = 4;
static const int PLOT_POWER_BY_SPEED = 5;

void calculateSpeed() {
    auto tyre = make_shared<Tyre>(185, 80, 13);
    auto transmission = make_shared<Transmission>(
            tyre,
            tyre,
            CommonDifferentials::VAZ::VAZ_2102(),
            CommonGearboxes::VAZ::VAZ_2101()
    );

    transmission->gearbox->shiftToGear(1);

    auto v_ptr = transmission->speedF();
    auto& v = * v_ptr;

    auto rpm_ptr = transmission->rotationF();
    auto& rpm = * rpm_ptr;

    fparams_t params;
    params["rotationSpeed"] = make_shared<Value>(950, CommonUnits::Get()->Speed->rpm)->convertToSi()->value;
    params["speed"] = make_shared<Value>(130, CommonUnits::Get()->Speed->KmPh)->convertToSi()->value;

    cout << "Skorostta e " << make_shared<Value>(v(params), CommonUnits::Get()->Speed->mPs)->convertTo(CommonUnits::Get()->Speed->KmPh)->value << endl;
    cout << "Oborotite sa " << make_shared<Value>(rpm(params), CommonUnits::Get()->Speed->radPs)->convertTo(CommonUnits::Get()->Speed->rpm)->value << endl;

}

void calculate(int what) {
    switch (what) {
        case PLOT_ENGINE_POWER_BY_ROD_LENGTH: EnginePowerCalculator::plotPowerByRodLength();
            break;
        case CALCULATE_OPTIMUM_REAR_SUSPENSION_BAR_LENGTHS: SuspensionCalculator::calculateRearSuspensionOptimalBarLengths();
            break;
        case CALCULATE_SPEED: calculateSpeed();
            break;
        case PLOT_MOMENTUM_AND_POWER: EnginePowerCalculator::plotMomentumAndPower();
            break;
        case PLOT_POWER_BY_SPEED: EnginePowerCalculator::plotPowerBySpeed();
            break;
        case EXIT:
            return;
        default: cout << "Unknown option, exiting" << endl;
    }

}

void printUsage() {
    cout << "To plot Engine power by Rod length, enter " << PLOT_ENGINE_POWER_BY_ROD_LENGTH << endl;
    cout << "To calculate optimum rear suspension bars lengths, enter " << CALCULATE_OPTIMUM_REAR_SUSPENSION_BAR_LENGTHS << endl;
    cout << "To plot momentum and power by RPM, enter " << PLOT_MOMENTUM_AND_POWER << endl;
    cout << "To plot power by speed, enter " << PLOT_POWER_BY_SPEED << endl;
    cout << "To Cancel, enter " << EXIT << endl;
}

int main() {

    printUsage();

    int option;
    cin >> option;
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    calculate(option);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    cout <<  "The execution took " << duration << "ms" << endl;
    return 0;
}
