#ifndef FUNCTION_H
#define FUNCTION_H

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace engc::math {

typedef std::function<double(const double &p1, const double &p2)> operator_t;

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
class Function {

public:
    virtual ~Function();

    /** \param params Аргументите на функцията. Преставлява речник име->стойност
     *  \return Стойността на функцията спрямо зададените аргументи.
     */
    virtual double value(const std::map<std::string, double> &params) const = 0;

private:

    class Aggregation;

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
        std::shared_ptr<Function> f1;
	std::shared_ptr<Function> f2;
	operator_t op;

    public:

	Aggregation(
	    const std::shared_ptr<Function> &f1,
	    const operator_t &op,
	    const std::shared_ptr<Function> &f2
	);

	virtual ~Aggregation();

        double value(const std::map<std::string, double> &p) const override;

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
