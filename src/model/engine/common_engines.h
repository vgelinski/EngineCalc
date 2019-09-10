#ifndef COMMON_ENGINES_H
#define COMMON_ENGINES_H

#include "engine.h"

namespace engc::model {
class CommonEngines {
public:
    class VAZ {
    public:
        static std::shared_ptr<Engine> VAZ_2101();
    };

};
}; //end namespace


#endif //COMMON_ENGINES_H
