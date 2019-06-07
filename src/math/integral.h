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
            fret_t start, fret_t end,
            const std::string &param,
            fret_t errBound,
            int threadCount = 1
    );

    /**\briefКлас, интегриращ функция по зададен аргумент.
    *
    * Класът моделира определен интеграл на функция по даден аргумент.
    * Резултатът е функция, която не зависи от съответния аргумент,
    * а само от останалите аргументи на първообраза.
    * Този клас използва методът на Симпсън за приближено изчисление.
    * Класът Класът ползва една единствена нишка за аритметични операции.
    * Приведеното по-долу описание е за функция на една променлива,
    * но обощението му за няколко променливи е тривиално.
    * Нека на интервала \f$[a,b]\f$ е зададена непрекъсната функция \f$f(x)\f$.
    * Разбиваме отсечката \f$[a,b]\f$ на \f$n\f$ равни части с дължина
    * \f$h=\frac{b - a}{n} = x_i - x_{i - 1}\f$. В резултат получаваме точките
    * \f$a = x_0<x_1<...<x_{n - 1}<x_n=b\f$, като при това
    * \f$x_i = x_{i - 1} + h = x_0 + hi\f$.
    * Построяваме трапци с основи \f$f(x_i)\f$ и \f$f(x_{i - 1})\f$
    * и височина \f$h\f$ Стойността на определения интеграл ще бъде сумата
    * от лицата на всички правоъгълници, или:
    * \f[
      \int_{a}^{b}f(x)dx =
       h . \left(\frac{f(x_0) + f(x_1)}{2} +
           \frac{f(x_1) + f(x_2)}{2} + ... + \frac{f(x_{n - 1}) + f(x_n)}{2}\right) =
       \frac{b - a}{n}\sum_{i = 0}^{n}f(x_i) - \frac{b - a}{n}.\frac{f(x_0) + f(x_n)}{2}
    \f]
    *
    * Съществуват по-точни методи за изчисление на определен интеграл (Метод на Симпсън),
    * но всички те оценяват грешката спрямо максималната стойност на някоя
    * производна на функцията. Тъй като нямаме функцията в аналитичен вид
    * и не е възможно лесно да пресметнем на колко отсечки да разделим интервала.
    * Затова опитваме да познаем \f$n\f$, след това пресмятаме още веднъж интеграла
    * с \f$2*n\f$ и т.н. докато стойностите на две поредни итерации се разминават
    * с по-малко от исканата точност.
    */
    class Integral : public Function {

    private:

        const static int THREAD_COUNT  = 16;

        const fret_t start, end, errBound;
        const std::shared_ptr<const Function> function;
        const std::string param;

    protected:

        virtual fret_t value(const fparams_t &params) const override;

    public:

        Integral(
                std::shared_ptr<const Function> f,
                fret_t start, fret_t end,
                const std::string &param,
                fret_t errBound
        );

        virtual ~Integral();

        virtual fvariables_t variables() const override;

     private:

        fret_t calculateForN(int n, fparams_t params) const;

        fret_t calculateAB(const fret_t &a, const fret_t &b,
                const fret_t &step, fparams_t params) const;
    };
};
}; //end namespace
#endif
