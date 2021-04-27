#include "UIObj.hpp"
#include <abyss/components/UI/base/IUpdate.hpp>
#include <abyss/components/UI/base/IDraw.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

namespace abyss::UI
{
    void UIObj::update()
    {
        for (auto&& com : this->finds<IUpdate>()) {
            com->onUpdate();
        }
    }

    void UIObj::draw() const
    {
        for (auto&& com : this->finds<IDraw>()) {
            com->onDraw();
        }
    }
    double UIObj::deltaTime() const
    {
        return this->getModule<GlobalTime>()->deltaTime();
    }
}
