#include "hurtip/libraries/math.hpp"

#include <stdexcept>
#include <utility>
#include <vector>
#include <cmath>

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

            functions.emplace(
            "sub",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'sub' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'sub' expects numeric arguments");
                }

                return *first - *second;
            });

            functions.emplace(
            "mul",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'mul' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'mul' expects numeric arguments");
                }

                return *first * *second;
            });

            functions.emplace(
            "div",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'div' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'div' expects numeric arguments");
                }

                return *first / *second;
            });

            functions.emplace(
            "pow",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'pow' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'pow' expects numeric arguments");
                }

                return std::pow(*first, *second);
            });

            functions.emplace(
            "sin",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'sin' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'sin' expects numeric argument");
                }

                return std::sin(*first);
            });

            functions.emplace(
            "cos",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'cos' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'cos' expects numeric argument");
                }

                return std::cos(*first);
            });

            functions.emplace(
            "tan",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'tan' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'tan' expects numeric argument");
                }

                return std::tan(*first);
            });

            functions.emplace(
            "asin",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'asin' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'asin' expects numeric argument");
                }

                return std::asin(*first);
            });

            functions.emplace(
            "acos",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'acos' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'acos' expects numeric argument");
                }
                
                return std::acos(*first);
            });

            functions.emplace(
            "atan",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'atan' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'atan' expects numeric argument");
                }
                
                return std::atan(*first);
            });

            functions.emplace(
            "abs",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'abs' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'abs' expects numeric argument");
                }
                
                return std::fabs(*first);
            });

            functions.emplace(
            "inv",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'inv' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'inv' expects numeric argument");
                }
                
                return 1 / *first;
            });

            functions.emplace(
            "exp",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'exp' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'exp' expects numeric argument");
                }
                
                return std::exp(*first);
            });

            functions.emplace(
            "log10",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'log10' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'log10' expects numeric argument");
                }
                
                return std::log10(*first);
            });

            functions.emplace(
            "log",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'log' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'log' expects numeric argument");
                }
                
                return std::log(*first);
            });

            functions.emplace(
            "log2",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'log2' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'log2' expects numeric argument");
                }
                
                return std::log2(*first);
            });

            functions.emplace(
            "sqrt",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'sqrt' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'sqrt' expects numeric argument");
                }
                
                return std::sqrt(*first);
            });

            functions.emplace(
            "cbrt",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'cbrt' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'cbrt' expects numeric argument");
                }
                
                return std::cbrt(*first);
            });

        functions.emplace(
            "sinh",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'sinh' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'sinh' expects numeric argument");
                }

                return std::sinh(*first);
            });

        functions.emplace(
            "cosh",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'cosh' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'cosh' expects numeric argument");
                }

                return std::cosh(*first);
            });

        functions.emplace(
            "tanh",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'tanh' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'tanh' expects numeric argument");
                }

                return std::tanh(*first);
            });

        functions.emplace(
            "asinh",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'asinh' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'asinh' expects numeric argument");
                }

                return std::asinh(*first);
            });

        functions.emplace(
            "acosh",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'acosh' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'acosh' expects numeric argument");
                }

                return std::acosh(*first);
            });

        functions.emplace(
            "atanh",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'atanh' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'atanh' expects numeric argument");
                }

                return std::atanh(*first);
            });

        functions.emplace(
            "atan2",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'atan2' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'atan2' expects numeric arguments");
                }

                return std::atan2(*second, *first);
            });

        interpreter.registerLibrary(
            "math",
            std::move(functions));
    }
}
