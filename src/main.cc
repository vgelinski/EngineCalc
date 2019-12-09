#include <chrono>
#include <iostream>
#include <stdio.h>

#include "tools/engine/engine_power_calculator.h"

using namespace std;
using namespace std::chrono;
using namespace engc::tools;

void calculation() {
    EnginePowerCalculator::plotPowerByRodLength();
}

int main() {
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    calculation();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    cout <<  "The execution took " << duration << "ms" << endl;
    return 0;
}
