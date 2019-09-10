#include "common_engines.h"

using namespace std;
using namespace engc::model;

#define CE CommonEngines

shared_ptr<Engine> CE::VAZ::VAZ2101() {
    return make_shared<Engine>();
}
