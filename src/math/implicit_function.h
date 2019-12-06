#ifndef IMPLICIT_FUNCTION_H
#define IMPLICIT_FUNCTION_H

#include "function.h"

namespace engc::math {

class ImplicitFunction : public Function {

protected:

    virtual fret_t value(const fparams_t& params) const override;
};
}; // end namespace


#endif //IMPLICIT_FUNCTION_H
