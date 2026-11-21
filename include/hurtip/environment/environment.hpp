
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>

namespace hurtip
{
    using RuntimeValue = std::variant<std::string, double, bool>;

    class Environment
    {
    public:
        explicit Environment(
            std::shared_ptr<Environment> parent = nullptr);

        void define(
            const std::string &name,
            const RuntimeValue &value);

        bool assign(
            const std::string &name,
            const RuntimeValue &value);

        bool get(
            const std::string &name,
            RuntimeValue &value) const;

        bool contains(const std::string &name) const;

    private:
        std::unordered_map<std::string, RuntimeValue> variables;

        std::shared_ptr<Environment> parent;
    };
}
