#include <chrono>
#include <iostream>
#include <stdio.h>

#include "math/constant.h"
#include "math/identity.h"

using namespace std;
using namespace std::chrono;
using namespace engc::math;

void calculation() {
    auto c5 = make_shared<Constant>(5);
    auto c3 = make_shared<Constant>(3);
    auto x = make_shared<Identity>("x");
    auto y = make_shared<Identity>("y");
    auto z = make_shared<Identity>("z");

    auto integralY_ptr = ((x + y * z) / (c5 - c3))->integrate(
        3.14, -18.4, "y", 0.0001);
    const auto &integralY = *integralY_ptr;
    fparams_t params;
    params["x"] = -20.0;
    params["y"] = 3.14;
    params["z"] = 0.002;
    params["unused"] = -1.0;

    printf("The value is %Lf\n", integralY(params));
}

int main() {
    
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    calculation();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>( t2 - t1 ).count();

    cout << duration << endl;
    return 0;
}
