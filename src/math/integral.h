#ifndef INTEGRAL_H
#define INTEGRAL_H

#include <memory>

#include "function.h"

namespace engc::math{

class IntegralCalculator {

private:

    friend class Function;

    static std::shared_ptr<Function> integrate(
            std::shared_ptr<const Function> f,
            double start, double end,
            const std::string &param,
            double errBound,
            int threadCount = 1
    );

    class SingleThreadIntegral : public Function {

    private:

    protected:

        virtual double value(const fparams_t &params) const override;

    public:

        SingleThreadIntegral(
                std::shared_ptr<const Function> f,
                double start, double end,
                const std::string &param,
                double errBound
        );

        virtual ~SingleThreadIntegral();

        virtual fvariables_t variables() const override;

    };
};
}; //end namespace
#endif
