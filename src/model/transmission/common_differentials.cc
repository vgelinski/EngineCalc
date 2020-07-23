#include "common_differentials.h"

using namespace std;
using namespace engc::model;

#define CD CommonDifferentials

shared_ptr<Differential> CD::VAZ::VAZ_2101() {
    return make_shared<Differential>(43.0L / 10.0L);
}

shared_ptr<Differential> CD::VAZ::VAZ_2102() {
    return make_shared<Differential>(40.0L / 9.0L);
}

shared_ptr<Differential> CD::VAZ::VAZ_2103() {
    return make_shared<Differential>(41.0L / 10.0L);
}

shared_ptr<Differential> CD::VAZ::VAZ_2106() {
    return make_shared<Differential>(43.0L / 11.0L);
}