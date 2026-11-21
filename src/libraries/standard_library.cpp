#include "hurtip/libraries/standard_library.hpp"
#include "hurtip/libraries/math.hpp"

namespace hurtip
{
    void registerStandardLibraries(Interpreter &interpreter)
    {
        registerMathLibrary(interpreter);
    }
}