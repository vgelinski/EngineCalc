#ifndef FUNCTION_H
#define FUNCTION_H

#include <map>
#include <string>

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
//    virtual ~Function();

    /** \param params Аргументите на функцията. Преставлява речник име->стойност
     *  \return Стойността на функцията спрямо зададените аргументи.
     */
    virtual double value(const std::map<std::string, double> &params) const = 0;
};

#endif
