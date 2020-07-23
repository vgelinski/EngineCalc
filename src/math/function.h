#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <unordered_set>

namespace engc::math {

typedef long double fret_t;
typedef std::function<fret_t(const fret_t& p1, const fret_t& p2)> operator_t;
typedef std::unordered_map<std::string, fret_t> fparams_t;
typedef std::unordered_set<std::string> fvariables_t;

/** \brief Клас, моделиращ математическа функция
 *
 * В математиката Функцията е съпоставяне на елементи от едно множество към
 * елементи на друго множество. Този клас моделира функции от типа
 * \f$I\!R^n \rightarrow I\!R\f$, тоест функция на \f$n\f$ променливи.
 * Поради практически съображения е въведено именуване на аргументите на
 * функцията. Конвенциите, които се спазват са следните:
 *   -# Редът на аргументите няма значение
 *   -# Ако на функцията се подадат допълнителни аргументи, то те се игнорират.
 *      Това позволява лесно разширение до функция на повече аргументи по
 *      време на изпълнение на програмата.
 *   -# Ако на функцията не са подадени минималният брой аргументи, от които се
 *      нуждае, поведението ѝ не е дефинирано.
 * 
 */
class Function : public std::enable_shared_from_this<Function> {

protected:

    /** \param params Аргументите на функцията. Преставлява речник име->стойност
     *  \return Стойността на функцията спрямо зададените аргументи.
     */
    virtual fret_t value(const fparams_t& params) const = 0;

public:

    virtual ~Function();

    /** Връща стойността на функцията, като извършва вътрешна оптимизация
    * вж. Function::value()
    */
    virtual fret_t operator()(const fparams_t& params) const;

    /** \brief Връща множеството от променливи на функцията
    *
    * Връща множеството от същински променливи на функцията.
    * Една променлива е същинска тогава и само тогава, когато 
    * съществуват две различни нейни стойности, такива че при еднакви стойности
    * на другите аргументи, функцията приема различни стойности.
    */
    virtual fvariables_t variables() const = 0;

    /** \brief Връща субституция на дадения аргумент с новото му име
    *
    * Връща Същата функция , в която обаче името на аргумента е променено
    * \param oldParamName старото име на аргумента
    * \param newParamName новото име на аргумента
    */
    virtual std::shared_ptr<const Function> substitute(
            const std::string& oldParamName,
            const std::string& newParamName) const;


    /** \brief Връща композиция на текущата функция с дадената
    * 
    * Връща композиция (Composition), в която указаният аргумент е заменен
    * от указаната функция.
    * \param other Функцията, която ще замени аргумента
    * \param paramName аргументът, който ще бъде заменен.
    */
    virtual std::shared_ptr<Function> compose(
            const std::shared_ptr<const Function> other,
            const std::string& paramName) const;

    /** \brief Пресмята определен интеграл от текущата функция
    *
    * Ако текущата функция е абстракция на
    * \f$f(x_1, x_2...x_{i-1}, x_i, x_{i + 1}...x_n): I\!R^n \rightarrow I\!R\f$,
    * то върнатата стойност
    * ще бъде абстракция на функцията
    * \f$g(x_1, x_2...x_{i - 1}, x_{i + 1}...x_n): I\!R^{n - 1} \rightarrow I\!R\f$
    * където:
    * 
    * \f$g(x_1, x_2...x_{i - 1}, x_{i + 1}...x_n) = \int_{a}^{b} f(x_1, x_2...x_n) dx_i\f$
    *
    * \param start долната граница на интеграла (а) в примера
    * \param end горната граница на интеграла (b) в примера
    * \param paramName аргументът, по който ще се интегрира (\f$x_i\f$) в примера
    * \param errBound допустимата погрешност при изчислението
    */
    virtual std::shared_ptr<Function> integrate(
            fret_t start, fret_t end,
            const std::string& paramName,
            fret_t errBound) const;

    virtual std::shared_ptr<Function> derive(const std::string& paramName, fret_t errBound) const;

private:

    class Aggregation;
    class Composition;

    friend std::shared_ptr<Function> operator+(
		    const std::shared_ptr<Function> lhs,
		    const std::shared_ptr<Function> rhs);

    friend std::shared_ptr<Function> operator-(
		    const std::shared_ptr<Function> lhs,
		    const std::shared_ptr<Function> rhs);

    friend std::shared_ptr<Function> operator*(
		    const std::shared_ptr<Function> lhs,
		    const std::shared_ptr<Function> rhs);

    friend std::shared_ptr<Function> operator/(
		    const std::shared_ptr<Function> lhs,
		    const std::shared_ptr<Function> rhs);
};

/** \brief Агрегация на две функции
 *
 * Класът моделира агрегацията на 2 функции и оператор. Стойността на
 * агрегацията (която сама по себе си е функция) е резултатът от изпълнението
 * на оператора върху стойностите на агрегираните функции
 */
class Function::Aggregation : public Function {
private:
    const std::shared_ptr<const Function> f1;
    const std::shared_ptr<const Function> f2;
    const operator_t op;

protected:

    fret_t value(const fparams_t& p) const override;

public:

    Aggregation(
        const std::shared_ptr<Function>& f1,
        const operator_t& op,
        const std::shared_ptr<Function>& f2
    );

    virtual ~Aggregation();

    virtual fvariables_t variables() const override;
};

/** \brief Клас, моделиращ композиция на две функции
*
* Ако означим с \f$f(x_1, x_2...x_n)\f$ 
* функция от тип \f$f:I\!R^n\rightarrow I\!R\f$
* и с \f$g(y_1, y_2...y_m)\f$
* функция от тип \f$f:I\!R^m\rightarrow I\!R\f$,
* то композицията на f и g, спрямо променливата \f$x_2\f$, ще бъде функцията
* \f$h(x_1, y_1, y_2...y_m, x_3...x_n) = f(x_1, g(y_1, y_2...y_m), x_3...x_n)\f$
* от тип \f$h:I\!R^{n + m - 1}\rightarrow I\!R\f$
*/
class Function::Composition : public Function {

private:

    const std::shared_ptr<const Function> superF;
    const std::shared_ptr<const Function> subF;
    const std::string paramName;

protected:

    fret_t value(const fparams_t& params) const override;

public:

    Composition(
            const std::shared_ptr<const Function> superF,
            const std::shared_ptr<const Function> subF,
            const std::string& paramName
    );

    virtual ~Composition();

    virtual fvariables_t variables() const override;
};


std::shared_ptr<Function> operator+(
		const std::shared_ptr<Function> lhs,
		const std::shared_ptr<Function> rhs);

std::shared_ptr<Function> operator-(
		const std::shared_ptr<Function> lhs,
		const std::shared_ptr<Function> rhs);

std::shared_ptr<Function> operator*(
		const std::shared_ptr<Function> lhs,
		const std::shared_ptr<Function> rhs);

std::shared_ptr<Function> operator/(
		const std::shared_ptr<Function> lhs,
		const std::shared_ptr<Function> rhs);

}; //end namespace

#endif
