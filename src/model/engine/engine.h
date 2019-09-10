#ifndef ENGINE_H
#define ENGINE_H

#include "../../math/function.h"
#include "../../physics/value.h"

namespace engc::model {

#define VAL std::shared_ptr<physics::Value>

class Engine : public std::enable_shared_from_this<Engine> {
private:

    static const std::string PISTON_COUNT;
    static const std::string PISTON_MASS;
    static const std::string CYLINDER_BORE;
    static const std::string STROKE_LENGTH;
    static const std::string ROD_LENGTH;
    static const std::string COMBUSTION_CHAMBER_VOLUME;
    static const std::string ROTATING_SPEED;

    int pistonCount;
    VAL pistonMass;
    VAL cylinderBore; //diameter
    VAL strokeLength;
    VAL rodLength;
    VAL combustionChamberVolume;

public:

    Engine(int pistonCount = 4);

    virtual ~Engine();

    virtual math::fparams_t getParams() const;

    /**
     * @brief Метод, изчисляващ механичната загуба в двигателя
     *
     * Ще използваме означенията на показаната схема. Ще разгледаме случая, когато няма отместване
     * и оста \f$OC\f$ съвпада с оста на цилиндъра (схема а)).
     *
     * \image html shema_kshm.png
     *
     * Нека ъгловата скорост на голяновия вал е \f$\omega\f$. Тогава ъгълът, между коляното
     * и оста (на схемата \f$\varphi\f$) след време \f$t\f$ ще бъде \f$\varphi(t) = \omega t\f$
     *
     * Да разгледаме триъгълник \f$ODC\f$. От синусовата теорема имаме \f$ \frac{l}{\sin \varphi} = \frac{r}{\sin \beta}\f$,
     * откъдето \f$ \sin \beta = \frac{r \sin \varphi}{l}\f$ и \f$ \cos \beta = \sqrt{1 - \frac{r^2 \sin^2 \varphi}{l^2}}\f$
     *
     * От същия триъгълник получаваме \f$OC = r \cos \varphi + l \cos \beta\f$
     *
     * От друга страна \f$X_\varphi(t) = AC = AO - OC = l + r - (r \cos \varphi + l \cos \beta) = l (1 - \cos \beta) + r (1 - \cos \varphi)\f$
     *
     * Тогава скоростта на буталото след време \f$t\f$  ще бъде \f$ \mathit{V}(t) = \frac{\partial X}{\partial t}\f$, а ускорението \f$\mathit{a}(t) = \frac{\partial^2 X}{\partial t^2}\f$.
     *
     * Силата, пораждаща това ускорение ще бъде \f$\mathit{F}(t) = am\f$
     *
     * Елементарната работа е \f$\delta A = F\mathrm{d}S = FV\mathrm{d}t\f$, а работата до момента t ще бъде \f$A = \int_{0}^{t}FV\mathrm{d}t\f$
     *
     * @return Механичната загуба в двигателя, измерена в Si единици за мощност (W)
     */
    virtual std::shared_ptr<math::Function> mechanicalLossF() const;

    virtual std::shared_ptr<Engine> setPistonMass(const VAL& pistonMass);
    virtual std::shared_ptr<Engine> setCylinderBore(const VAL& cylinderBore);
    virtual std::shared_ptr<Engine> setStrokeLength(const VAL& strokeLength);
    virtual std::shared_ptr<Engine> setRodLength(const VAL& rodLength);
    virtual std::shared_ptr<Engine> setCombustionChamberVolume(const VAL& combustionChamberVolume);
    virtual std::shared_ptr<Engine> setCombustionRatio(const long double& ratio);

};

#undef VAL
};
#endif //ENGINE_H
