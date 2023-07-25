#include <abyss/modules/UI/base/UIObj.hpp>

#include <abyss/modules/UI/base/IUpdate.hpp>
#include <abyss/modules/UI/base/IPostUpdate.hpp>
#include <abyss/modules/UI/base/IDraw.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>

namespace abyss::UI
{
    void UIObj::update()
    {
        for (auto&& com : this->finds<IUpdate>()) {
            com->onUpdate();
        }
    }

    void UIObj::postUpdate()
    {
        for (auto&& com : this->finds<IPostUpdate>()) {
            com->onPostUpdate();
        }
    }

    void UIObj::draw() const
    {
        auto drawer = this->getModule<DrawManager>();
        for (auto&& com : this->finds<IDraw>()) {
            drawer->add(com->getLayer(), [com] {
                com->onDraw();
            }, com->getOrder());
        }
    }
    double UIObj::deltaTime() const
    {
        return this->getModule<GlobalTime>()->deltaTime();
    }
    s3d::ISteadyClock* UIObj::getClock() const
    {
        return this->getModule<GlobalTime>();
    }
    bool UIObj::isActive(const Filter& filter) const
    {
        return GameObject::isActive() && m_filter.isActive(filter);
    }
}
