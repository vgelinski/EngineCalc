#include "illegal_argument_exception.h"

using namespace std;
using namespace engc::util;

#define IAE IllegalArgumentException

IAE::IAE(const string& what) : runtime_error(what), WHAT(what) {}

IAE::~IAE() {}

const char* IAE::what() const noexcept {
    return WHAT.c_str();
}
