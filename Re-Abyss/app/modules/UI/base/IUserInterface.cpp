#include "IUserInterface.hpp"
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

namespace abyss::ui
{
    void IUserInterface::update()
    {
        for (auto&& com : this->finds<IUpdate>()) {
            com->onUpdate();
        }
    }

    void IUserInterface::draw() const
    {
        for (auto&& com : this->finds<IDraw>()) {
            com->onDraw();
        }
    }
    double IUserInterface::deltaTime() const
    {
        return this->getModule<GlobalTime>()->deltaTime();
    }
}
