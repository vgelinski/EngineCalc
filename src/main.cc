#include <chrono>
#include <iostream>
#include <stdio.h>

#include "tools/engine/engine_power_calculator.h"

using namespace std;
using namespace std::chrono;
using namespace engc::tools;

static const int EXIT = 0;
static const int PLOT_ENGINE_POWER_BY_ROD_LENGTH = 1;
static const int CALCULATE_OPTIMUM_REAR_SUSPENSION_BARS_LENGTH = 2;

void calculate(int what) {
    switch (what) {
        case PLOT_ENGINE_POWER_BY_ROD_LENGTH: EnginePowerCalculator::plotPowerByRodLength();
            break;
        case CALCULATE_OPTIMUM_REAR_SUSPENSION_BARS_LENGTH: int a;
            break;
        case EXIT:
            return;
        default: cout << "Unknown option, exiting" << endl;
    }

}

void printUsage() {
    cout << "To plot Engine power by Rod length, enter " << PLOT_ENGINE_POWER_BY_ROD_LENGTH << endl;
    cout << "To calculate optimum rear suspension rods length, enter " << CALCULATE_OPTIMUM_REAR_SUSPENSION_BARS_LENGTH << endl;
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
