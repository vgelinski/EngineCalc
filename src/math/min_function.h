#ifndef ENGINECALC_MIN_FUNCTION_H
#define ENGINECALC_MIN_FUNCTION_H

#include "function.h"

namespace engc::math {
class MinFunction : public Function {
private:
    std::unordered_set<std::shared_ptr<Function>> functions;

protected:
    virtual fret_t value(const fparams_t& params) const override;

public:
    MinFunction();
    virtual ~MinFunction();

    virtual fvariables_t variables() const override;
    virtual void addFunction(const std::shared_ptr<Function>& f);

};
};

#endif //ENGINECALC_MIN_FUNCTION_H
