#include "suspension_calculator.h"

#include <cmath>
#include <iostream>
#include <stdio.h>

#include "../../math/constant.h"
#include "../../math/custom_function.h"
#include "../../math/identity.h"
#include "../../math/implicit_function.h"
#include "../../math/extremum_calculator.h"
#include "../../physics/common_units.h"

using namespace std;
using namespace engc::math;
using namespace engc::physics;
using namespace engc::tools;

#define SC SuspensionCalculator
#define CU CommonUnits

const shared_ptr<Value> SC::CD = make_shared<Value>(130.0L, CU::Length::mm);
const shared_ptr<Value> SC::Xd = make_shared<Value>(330.0L, CU::Length::mm);
const shared_ptr<Value> SC::Yd = make_shared<Value>(85.0L, CU::Length::mm);
const shared_ptr<Value> SC::Ya_MIN = make_shared<Value>(-120.0L, CU::Length::mm);
const shared_ptr<Value> SC::Ya_MAX = make_shared<Value>(-20.0L, CU::Length::mm);
const shared_ptr<Value> SC::R_MIN = make_shared<Value>(595.0L, CU::Length::mm);
const shared_ptr<Value> SC::R_MAX = make_shared<Value>(615.0L, CU::Length::mm);
const shared_ptr<Value> SC::r_MIN = make_shared<Value>(290.0L, CU::Length::mm);
const shared_ptr<Value> SC::r_MAX = make_shared<Value>(310.0L, CU::Length::mm);
const shared_ptr<Value> SC::ERR_BOUND = make_shared<Value>(1.0L, CU::Length::Hundredthmm);

shared_ptr<Function> SC::sq(const shared_ptr <Function>& f) {
    return f * f;
}

void SC::calculateRearSuspensionOptimalBarLengths() {
    auto yAF = make_shared<Identity>("ya");
    auto RF = make_shared<Identity>("R");
    auto rF = make_shared<Identity>("r");
    auto sqrtF = make_shared<CustomFunction>([](const fparams_t& params){
        return sqrt(params.at("param"));
    }, fvariables_t({"param"}));

    auto xAF = sqrtF->compose((sq(RF) - sq(yAF)), "param");
    auto xBF = make_shared<Identity>("xb");
    auto xDF = make_shared<Constant>(Xd->convertToSi()->value);
    auto yDF = make_shared<Constant>(Yd->convertToSi()->value);
    auto yBF_xBF = yDF - sqrtF->compose((sq(rF) - sq(xBF - xDF)), "param");  //yBF(xBF)

    auto cdF = make_shared<Constant>(CD->convertToSi()->value);
    auto fF = sq(xBF - xAF) + sq(yBF_xBF - yAF) - sq(cdF);
    auto xBFExplicit = make_shared<ImplicitFunction>(fF,
            "xb",
            make_shared<Value>(605.0L, CU::Length::mm)->convertToSi()->value,
            make_shared<Value>(645.0L, CU::Length::mm)->convertToSi()->value,
            ERR_BOUND->convertToSi()->value * 1800 //TODO debug why so big errBound is needed
            );
    auto xCF = (xAF + xBFExplicit) / make_shared<Constant>(2.0L);

    auto xCMinF = xCF->compose(make_shared<Identity>("yAmin"), "ya");
    auto xCMaxF = xCF->compose(make_shared<Identity>("yAmax"), "ya");
    auto dxcF = xCMaxF - xCMinF;

    fparams_t params;
    params["yAmin"] = Ya_MIN->convertToSi()->value;
    params["yAmax"] = Ya_MAX->convertToSi()->value;

    auto calc = make_shared<ExtremumCalculator>(dxcF, params, ERR_BOUND->convertToSi()->value);

    calc->setParamBound("R", R_MIN->convertToSi()->value, R_MAX->convertToSi()->value);
    calc->setParamBound("r", r_MIN->convertToSi()->value, r_MAX->convertToSi()->value);
    calc->calculate();

    cout << "Optimal lengths are as follows:" <<  endl;
    cout << "\tR min: " << make_shared<Value>(calc->minAt()["R"], CU::Length::m)->convertTo(CU::Length::mm)->value << "mm" <<  endl;
    cout << "\tR max: " << make_shared<Value>(calc->maxAt()["R"], CU::Length::m)->convertTo(CU::Length::mm)->value << "mm" <<  endl;
    cout << "\tr min: " << make_shared<Value>(calc->minAt()["r"], CU::Length::m)->convertTo(CU::Length::mm)->value << "mm" <<  endl;
    cout << "\tr max: " << make_shared<Value>(calc->maxAt()["r"], CU::Length::m)->convertTo(CU::Length::mm)->value << "mm" <<  endl;
    cout << "\tmax: " << make_shared<Value>(calc->maxVal(), CU::Length::m)->convertTo(CU::Length::mm)->value << "mm" <<  endl;
    cout << "\tmin: " << make_shared<Value>(calc->minVal(), CU::Length::m)->convertTo(CU::Length::mm)->value << "mm" <<  endl;
//    cout << "\tR: " << make_shared<Value>(calc->maxAt()["R"], CU::Length::m)->convertTo(CU::Length::mm)->toString() <<  endl;
//    cout << "\tr: " << make_shared<Value>(calc->maxAt()["r"], CU::Length::m)->convertTo(CU::Length::mm)->toString() <<  endl;
}
