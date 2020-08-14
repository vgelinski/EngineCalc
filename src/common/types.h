#ifndef ENGINECALC_TYPES_H
#define ENGINECALC_TYPES_H

#include <functional>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>


namespace engc {
    namespace math {
        typedef long double fret_t;
        typedef std::function<fret_t(const fret_t& p1, const fret_t& p2)> operator_t;
        typedef std::unordered_map<std::string, fret_t> fparams_t;
        typedef std::unordered_set<std::string> fvariables_t;
    };
    namespace physics {
        typedef std::optional<std::string> uname_t;
    };
};
#endif //ENGINECALC_TYPES_H
