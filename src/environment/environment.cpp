
#include "hurtip/environment/environment.hpp"

#include <utility>

namespace hurtip
{
Environment::Environment(std::shared_ptr<Environment> parent) : parent(std::move(parent)) {}

bool Environment::define(const std::string& name, const RuntimeValue& value)
{
    if (variables.find(name) != variables.end())
    {
        return false;
    }

    variables.emplace(name, value);

    return true;
}

bool Environment::assign(const std::string& name, const RuntimeValue& value)
{
    auto variable = variables.find(name);

    if (variable != variables.end())
    {
        variable->second = value;
        return true;
    }

    if (parent)
    {
        return parent->assign(name, value);
    }

    return false;
}

bool Environment::get(const std::string& name, RuntimeValue& value) const
{
    auto variable = variables.find(name);

    if (variable != variables.end())
    {
        value = variable->second;
        return true;
    }

    if (parent)
    {
        return parent->get(name, value);
    }

    return false;
}

bool Environment::contains(const std::string& name) const
{
    if (variables.find(name) != variables.end())
    {
        return true;
    }

    return parent && parent->contains(name);
}
} // namespace hurtip
