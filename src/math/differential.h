#ifndef DIFFERENTIAL_H
#define DIFFERENTIAL_H

#include <memory>

#include "function.h"

namespace engc::math{

class DifferentialCalculator {

private:

    friend class Function;

    static std::shared_ptr<Function> differentiate(
            std::shared_ptr<const Function> f,
            const std::string &param,
            fret_t errBound
    );

    /**\briefКлас, диференциращ функция по зададен аргумент.
    *
    * Класът моделира частна производна на функция по даден аргумент.
    */
    class Differential : public Function {

    private:

        const std::shared_ptr<const Function> function;
        const std::string param;

    protected:

        virtual fret_t value(const fparams_t &params) const override;

    public:

        Differential(
                std::shared_ptr<const Function> f,
                const std::string &param,
                fret_t errBound
        );

        virtual ~Differential();

        virtual fvariables_t variables() const override;

    private:

        fret_t calculateForDx(const fret_t& dx, fparams_t params) const;
    };

};
}; //end namespace


#endif //DIFFERENTIAL_CALCULATOR_H
