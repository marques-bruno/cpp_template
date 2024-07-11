#include "myproject/myproject.h"

#include <stdexcept>
#include <string>
#include "myproject1_impl.h"

namespace myproject
{
float foo(float a, float b, char op)
{
    switch (op)
    {
        case '+':
            return details::add(a, b);
        case '*':
            return details::mult(a, b);
        default:
            throw std::invalid_argument((std::string("unknown operand ") + op).c_str());
    }
    return .0F;
}
}  // namespace myproject
