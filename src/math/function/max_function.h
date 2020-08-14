#ifndef ENGINECALC_MAX_FUNCTION_H
#define ENGINECALC_MAX_FUNCTION_H

#include "function.h"

namespace engc::math {
class MaxFunction : public Function {
private:
    std::unordered_set<std::shared_ptr<Function>> functions;

protected:
    virtual fret_t value(const fparams_t& params) const override;

    virtual std::string toStringImpl() const override;

public:
    MaxFunction();
    virtual ~MaxFunction();

    virtual fvariables_t variables() const override;
    virtual void addFunction(const std::shared_ptr<Function>& f);

};
};


#endif //ENGINECALC_MAX_FUNCTION_H
