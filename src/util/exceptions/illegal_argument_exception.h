#ifndef ILLEGAL_ARGUMENT_EXCEPTION_H
#define ILLEGAL_ARGUMENT_EXCEPTION_H

#include <stdexcept>

namespace engc::util {

class IllegalArgumentException : public std::runtime_error {
private:

    const std::string WHAT;
public:

    IllegalArgumentException(const std::string& what);
    virtual ~IllegalArgumentException();

    virtual const char* what() const noexcept;
};
}; //end namespace
#endif
