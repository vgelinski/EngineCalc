#ifndef COMMON_ENGINES_H
#define COMMON_ENGINES_H

#include "engine.h"

namespace engc::model {
class CommonEngines {
public:
    class VAZ {
    public:
        static std::shared_ptr<Engine> VAZ_2101();
        static std::shared_ptr<Engine> VAZ_21011();
        static std::shared_ptr<Engine> VAZ_2103();
        static std::shared_ptr<Engine> VAZ_2105();
        static std::shared_ptr<Engine> VAZ_2106();
    };

};
}; //end namespace


#endif //COMMON_ENGINES_H
