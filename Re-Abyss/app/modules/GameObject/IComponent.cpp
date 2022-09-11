#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss
{
    Executer::Command Executer::onStart() const
    {
        return on<IComponent>();
    }
    Executer::Command Executer::onEnd() const
    {
        return on<IComponent>();
    }
}
