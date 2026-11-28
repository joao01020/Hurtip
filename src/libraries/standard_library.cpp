#include "hurtip/libraries/standard_library.hpp"
#include "hurtip/libraries/math.hpp"
#include "hurtip/libraries/string.hpp"

namespace hurtip
{
    void registerStandardLibraries(Interpreter &interpreter)
    {
        registerMathLibrary(interpreter);
        registerStringLibrary(interpreter);
    }
}
