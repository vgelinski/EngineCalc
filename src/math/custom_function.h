#ifndef CUSTOM_FUNCTION_H
#define CUSTOM_FUNCTION_H

#include "function.h"

#include <functional>

namespace engc::math {

class CustomFunction : public Function {

private:

    const std::function<fret_t(fparams_t)> custF;
    const fvariables_t vars;

protected:


    virtual fret_t value(const fparams_t& params) const override;

public:

    CustomFunction(const std::function<fret_t(fparams_t)>& cf, const fvariables_t& vars);
    ~CustomFunction();

    virtual fvariables_t variables() const override;

};
}; // end namespace


#endif //CUSTOM_FUNCTION_H
