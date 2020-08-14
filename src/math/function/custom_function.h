#ifndef CUSTOM_FUNCTION_H
#define CUSTOM_FUNCTION_H

#include "function.h"

#include <functional>

namespace engc::math {

class CustomFunction : public Function {

private:

    const std::function<fret_t(const fparams_t&)> custF;
    const fvariables_t vars;
    const std::string representation;

protected:


    virtual fret_t value(const fparams_t& params) const override;
    virtual std::string toStringImpl() const override;

public:

    CustomFunction(
            const std::function<fret_t(const fparams_t&)>& cf,
            const fvariables_t& vars,
            const std::string& representation = "unknown_custom_function"
    );
    ~CustomFunction();

    virtual fvariables_t variables() const override;

};
}; // end namespace


#endif //CUSTOM_FUNCTION_H
