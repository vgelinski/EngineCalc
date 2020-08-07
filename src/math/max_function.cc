#include "max_function.h"

#include <numeric>

using namespace std;
using namespace engc::math;

#define MF MaxFunction

MF::MF() {}
MF::~MF() {}

fret_t MF::value(const fparams_t& params) const {
    return std::accumulate(
            functions.begin(),
            functions.end(),
            (** functions.begin())(params),
            [params](const fret_t& acc, const shared_ptr<Function>& f) -> fret_t {
                auto val = (*f)(params);
                return val > acc ? val : acc;
            }
    );
}

string MF::toStringImpl() const {
    string ret = "max\\left(";
    std::accumulate(
            functions.begin(),
            functions.end(),
            0,
            [&ret](int index, const shared_ptr<Function>& f) -> int {
                if (index == 0) {
                    ret.append(f->toString());
                } else {
                    ret.append(", " + f->toString());
                }
                return index + 1;
            }
    );
    ret.append("\\right)");
    return ret;
};

fvariables_t MF::variables() const {
    return std::accumulate(
            functions.begin(),
            functions.end(),
            fvariables_t({}),
            [](const fvariables_t& acc, const shared_ptr<Function>& f) -> fvariables_t {
                fvariables_t ret;
                auto vars = f->variables();
                set_union(
                        acc.begin(), acc.end(),
                        vars.begin(), vars.end(),
                        inserter(ret, ret.begin())
                );
                return ret;
            }
    );
}

void MF::addFunction(const shared_ptr<Function>& f) {
    functions.insert(f);
}