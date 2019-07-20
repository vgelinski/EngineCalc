#ifndef ENGINE_H
#define ENGINE_H

#include "../../math/function.h"
#include "../../physics/value.h"

namespace engc::model {

#define VAL std::shared_ptr<physics::Value>

class Engine : public std::enable_shared_from_this<Engine> {
private:

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
