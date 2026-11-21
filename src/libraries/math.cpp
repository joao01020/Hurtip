#include "hurtip/libraries/math.hpp"

#include <stdexcept>
#include <utility>
#include <vector>

namespace hurtip
{
    void registerMathLibrary(Interpreter &interpreter)
    {
        Interpreter::NativeFunctionRegistry functions;

        functions.emplace(
            "sum",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'sum' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'sum' expects numeric arguments");
                }

                return *first + *second;
            });

        interpreter.registerLibrary(
            "math",
            std::move(functions));
    }
}