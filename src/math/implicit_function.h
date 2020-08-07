#ifndef IMPLICIT_FUNCTION_H
#define IMPLICIT_FUNCTION_H

#include <limits>

#include "function.h"

namespace engc::math {

/** \brief Клас, моделиращ неявна функция
 *
 * Нека \f$F(x_1, x_2...x_n, y)\f$ е функция, която за произволни фиксирани \f$x_i\f$ е монотонна
 * спрямо \f$y\f$. Тогава при фиксирани \f$x_i\f$ уравнението \f$F(x_1, x_2...x_n, y) = 0\f$
 * има единствено решение \f$y_0\f$ (ако въобще има). Тъй като то се определя еднозначно от
 * избраните стойности на \f$x_i\f$, казваме че е дефинирана неявната функция \f$y=f(x_1, x_2...x_n)\f$
 * Именно тази функция моделира текущия клас.
 *
 */
class ImplicitFunction : public Function {
private:

    const std::shared_ptr<Function> F;
    const std::string pName;
    const fret_t start;
    const fret_t end;
    const fret_t err_bound;

    bool equals(const fret_t& a, const fret_t& b) const;
    inline fret_t val(fparams_t& params, const fret_t& arg) const;
    fret_t solveFor(const fret_t& left, const fret_t& right, fparams_t& params) const;

protected:

    /**
     * Методът изчислява стойността на функцията с точност, зададена в конструктора. Търсената
     * стойност принадлежи на интервал, също зададен в конструктора. В началото се извършва
     * проверка дали някой от краищата на интервала не е търсената стойност. В случай че не е
     * се проверява средата на интервала. Ако тя също не е решение, то се взима интервал с краища
     * средата и онзи край, чиято ф-на стойност се различава по знак с ф-ната стойност на средата
     * и се прилага същият алгоритъм. Тъй като функцията е монотонна, то ние неограничено ще се
     * приближаваме до търсената стойност и след краен брой стъпки я намерим с произволна точност,
     * макар че истинската стойност може и да не е достижима след краен брой стъпки.
     */
    virtual fret_t value(const fparams_t& params) const override;

    virtual std::string toStringImpl() const override;

public:

    ImplicitFunction(
            const std::shared_ptr<Function>& F,
            const std::string& pName,
            const fret_t& start = std::numeric_limits<fret_t >::min() / 2,
            const fret_t& end = std::numeric_limits<fret_t >::max() / 2,
            const fret_t& err_bound = 0.00000001
    );
    virtual ~ImplicitFunction();

    virtual fvariables_t variables() const override;
};
}; // end namespace


#endif //IMPLICIT_FUNCTION_H
