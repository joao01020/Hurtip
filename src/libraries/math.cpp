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

                return std::atan2(*first, *second);
            });

        functions.emplace(
            "floor",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'floor' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'floor' expects numeric argument");
                }

                return std::floor(*first);
            });

        functions.emplace(
            "ceil",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'ceil' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'ceil' expects numeric argument");
                }

                return std::ceil(*first);
            });

        functions.emplace(
            "mod",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'mod' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'mod' expects numeric arguments");
                }

                return std::fmod(*first, *second);
            });

        functions.emplace(
            "round",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'round' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'round' expects numeric argument");
                }

                return std::round(*first);
            });
        
        functions.emplace(
            "trunc",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'trunc' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'trunc' expects numeric argument");
                }

                return std::trunc(*first);
            });

        functions.emplace(
            "hypot",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'hypot' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'hypot' expects numeric arguments");
                }

                return std::hypot(*first, *second);
            });

        functions.emplace(
            "logHypot",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error(
                        "Function 'logHypot' expects exactly 2 arguments");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                const double *second =
                    std::get_if<double>(&arguments[1]);

                if (!first || !second)
                {
                    throw std::runtime_error(
                        "Function 'logHypot' expects numeric arguments");
                }

                return std::log(std::hypot(*first, *second));
            });

        functions.emplace(
            "sign",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'sign' expects exactly 1 argument");
                }

                const double *first =
                    std::get_if<double>(&arguments[0]);

                if (!first)
                {
                    throw std::runtime_error(
                        "Function 'sign' expects numeric argument");
                }

                 return (*first > 0) ? 1.0 : ((*first < 0) ? -1.0 : 0.0);
            });

        functions.emplace("PI", [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue {
            if (arguments.size() != 0) throw std::runtime_error("PI takes no arguments");
            return 3.14159265358979323846;
        });

        functions.emplace("E", [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue {
            if (arguments.size() != 0) throw std::runtime_error("E takes no arguments");
            return 2.71828182845904523;
        });

        functions.emplace("PHI", [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue {
            if (arguments.size() != 0) throw std::runtime_error("PHI takes no arguments");
            return 1.61803398874989484;
        });
    
        interpreter.registerLibrary(
            "math",
            std::move(functions));
    }
}
