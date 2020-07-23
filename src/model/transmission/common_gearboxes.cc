#include "common_gearboxes.h"

using namespace std;
using namespace engc::math;
using namespace engc::model;

#define CG CommonGearboxes

shared_ptr<Gearbox> CG::VAZ::VAZ_2101() {
    return make_shared<Gearbox>(vector<fret_t>({-3.867L, 3.753L, 2.303L, 1.493, 1.0L}));
}

shared_ptr<Gearbox> CG::VAZ::VAZ_2105() {
    return make_shared<Gearbox>(vector<fret_t>({-3.53L, 3.667L, 2.1L, 1.361, 1.0L, 0.801L}));
}

shared_ptr<Gearbox> CG::VAZ::VAZ_2106() {
    return make_shared<Gearbox>(vector<fret_t>({-3.340L, 3.242L, 1.989L, 1.289, 1.0L}));
}

shared_ptr<Gearbox> CG::VAZ::R1() {
    return make_shared<Gearbox>(vector<fret_t>({0.0L, 3.242L, 1.989L, 1.289, 1.0L, 0.759L}));
}

shared_ptr<Gearbox> CG::VAZ::R2() {
    return make_shared<Gearbox>(vector<fret_t>({0.0L, 3.007L, 1.989L, 1.289, 1.0L, 0.759L}));
}

shared_ptr<Gearbox> CG::VAZ::R3() {
    return make_shared<Gearbox>(vector<fret_t>({0.0L, 2.424L, 1.768L, 1.240, 1.0L, 0.585L}));
}

shared_ptr<Gearbox> CG::VAZ::R4() {
    return make_shared<Gearbox>(vector<fret_t>({0.0L, 3.242L, 1.675L, 1.186, 1.0L, 0.585L}));
}