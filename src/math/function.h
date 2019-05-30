#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <map>
#include <memory>
#include <string>
#include <unordered_set>

namespace engc::math {

typedef std::function<double(const double &p1, const double &p2)> operator_t;
typedef std::map<std::string, double> fparams_t;
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
    virtual double value(const fparams_t &params) const = 0;

public:

    virtual ~Function();

    /** Връща стойността на функцията, като извършва вътрешна оптимизация
    * вж. Function::value()
    */
    virtual double operator()(const fparams_t &params) const;

    /** \brief Връща множеството от променливи на функцията
    *
    * Връща множеството от същински променливи на функцията.
    * Една променлива е същинска тогава и само тогава, когато 
    * съществуват две различни нейни стойности, такива че при еднакви стойности
    * на другите аргументи, функцията приема различни стойности.
    */
    virtual fvariables_t variables() const = 0;

    virtual std::shared_ptr<Function> compose(
            const std::shared_ptr<Function> other,
            const std::string &paramName) const;

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

    double value(const std::map<std::string, double> &p) const override;

public:

    Aggregation(
        const std::shared_ptr<Function> &f1,
        const operator_t &op,
        const std::shared_ptr<Function> &f2
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

    double value(const std::map<std::string, double> &params) const override;

public:

    Composition(
            const std::shared_ptr<const Function> superF,
            const std::shared_ptr<const Function> subF,
            const std::string &paramName
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
