#include "hurtip/libraries/string.hpp"

#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>

namespace hurtip
{
    void registerStringLibrary(Interpreter &interpreter)
    {
        Interpreter::NativeFunctionRegistry functions;

        functions.emplace(
            "indexOf",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error("Function 'indexOf' expects exactly 2 arguments");
                }

                const std::string *str = std::get_if<std::string>(&arguments[0]);
                const std::string *search = std::get_if<std::string>(&arguments[1]);

                if (!str || !search)
                {
                    throw std::runtime_error("Function 'indexOf' expects string arguments");
                }

                std::size_t pos = str->find(*search);
                
                if (pos == std::string::npos) {
                    return -1.0;
                }
                return (double)pos;
            });

        functions.emplace(
            "lastIndexOf",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error("Function 'lastIndexOf' expects exactly 2 arguments");
                }

                const std::string *str = std::get_if<std::string>(&arguments[0]);
                const std::string *search = std::get_if<std::string>(&arguments[1]);

                if (!str || !search)
                {
                    throw std::runtime_error("Function 'lastIndexOf' expects string arguments");
                }

                std::size_t pos = str->rfind(*search);
                
                if (pos == std::string::npos) {
                    return -1.0;
                }
                return (double)pos;
            });

            functions.emplace(
                "charAt",
                [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
                {
                    if (arguments.size() != 2)
                    {
                        throw std::runtime_error(
                            "Function 'charAt' expects exactly 2 arguments");
                    }

                    const std::string *str =
                        std::get_if<std::string>(&arguments[0]);

                    const double *index =
                        std::get_if<double>(&arguments[1]);

                    if (!str || !index)
                    {
                        throw std::runtime_error(
                            "Function 'charAt' expects a string and a numeric argument");
                    }

                    if (*index < 0 || *index != std::floor(*index))
                    {
                        throw std::runtime_error("Index must be a non-negative integer");
                    }

                    if (*index >= str->size())
                    {
                        throw std::runtime_error("Index exceeds string length");
                    }

                    return std::string(1, str->at(static_cast<std::size_t>(*index)));
                });

        functions.emplace(
            "slice",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 3)
                {
                    throw std::runtime_error("Function 'slice' expects exactly 3 arguments");
                }

                const std::string *str = std::get_if<std::string>(&arguments[0]);
                const double *l1 = std::get_if<double>(&arguments[1]);
                const double *l2 = std::get_if<double>(&arguments[2]);

                if (!str || !l1 || !l2)
                {
                    throw std::runtime_error("Function 'slice' expects one string arguments and two numerics arguments");
                }

                if (*l1 < 0 || *l1 != std::floor(*l1) || *l2 < 0 || *l2 != std::floor(*l2))
                {
                    throw std::runtime_error("Index must be a non-negative integer");
                }

                if (*l1 > (*str).size() - 1 || *l2 > (*str).size() - 1) {
                    throw std::runtime_error("Function 'slice' expects a start limit and the end less or equal the size of string");
                }

                if (*l1 > *l2) {
                    throw std::runtime_error("Function 'slice' expects a start limit less or equal than the end");
                }

                if (*l1 > std::numeric_limits<std::size_t>::max() || *l2 > std::numeric_limits<std::size_t>::max())
                {
                    throw std::runtime_error("Index exceeds size_t limit");
                }

                std::size_t start = static_cast<std::size_t>(*l1);
                std::size_t end = static_cast<std::size_t>(*l2);

                return (*str).substr(start, end - start + 1);
            });

        functions.emplace(
            "reverse",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error("Function 'reverse' expects exactly 1 argument");
                }

                const std::string *str = std::get_if<std::string>(&arguments[0]);

                if (!str)
                {
                    throw std::runtime_error("Function 'reverse' expects string argument");
                }

                std::string result = *str;

                std::reverse(result.begin(), result.end());

                return result;
            });

        functions.emplace(
            "length",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error("Function 'length' expects exactly 1 argument");
                }

                const std::string *str = std::get_if<std::string>(&arguments[0]);

                if (!str)
                {
                    throw std::runtime_error("Function 'length' expects string argument");
                }

                return static_cast<double>((*str).size());
            });

        functions.emplace(
            "includes",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error("Function 'includes' expects exactly 2 arguments");
                }

                const std::string *str = std::get_if<std::string>(&arguments[0]);
                const std::string *search = std::get_if<std::string>(&arguments[1]);

                if (!str || !search)
                {
                    throw std::runtime_error("Function 'includes' expects string arguments");
                }
                
                if (str->find(*search) == std::string::npos) {
                    return false;
                }
                return true;
            });

        functions.emplace(
            "startsWith",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 2)
                {
                    throw std::runtime_error("Function 'startsWith' expects exactly 2 arguments");
                }

                const std::string *str = std::get_if<std::string>(&arguments[0]);
                const std::string *search = std::get_if<std::string>(&arguments[1]);

                if (!str || !search)
                {
                    throw std::runtime_error("Function 'startsWith' expects string arguments");
                }
                
                return str->find(*search) == 0;
            });

        functions.emplace(
            "isNumeric",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'isNumeric' expects exactly 1 argument");
                }

                const std::string *str =
                    std::get_if<std::string>(&arguments[0]);

                if (!str)
                {
                    throw std::runtime_error(
                        "Function 'isNumeric' expects a string argument");
                }

                if (str->empty())
                {
                    return false;
                }

                char *end = nullptr;
                std::strtod(str->c_str(), &end);

                return end != str->c_str() &&
                    *end == '\0';
            });

        functions.emplace(
            "toNumber",
            [](const std::vector<RuntimeValue> &arguments) -> RuntimeValue
            {
                if (arguments.size() != 1)
                {
                    throw std::runtime_error(
                        "Function 'toNumber' expects exactly 1 argument");
                }

                const std::string *str =
                    std::get_if<std::string>(&arguments[0]);

                if (!str)
                {
                    throw std::runtime_error(
                        "Function 'toNumber' expects a string argument");
                }

                try
                {
                    std::size_t pos;
                    double result = std::stod(*str, &pos);

                    if (pos != str->size())
                    {
                        throw std::runtime_error("Invalid numeric string");
                    }

                    return result;
                }
                catch (const std::invalid_argument &)
                {
                    throw std::runtime_error("Invalid numeric string");
                }
                catch (const std::out_of_range &)
                {
                    throw std::runtime_error("Numeric value out of range");
                }
            });

        interpreter.registerLibrary(
            "string",
            std::move(functions));
    }
}