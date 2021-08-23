#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>

namespace abyss::Effect::Bubble
{
    class LifeTime :
        public IComponent,
        public IUpdate
    {
    public:
        LifeTime(EffectObj* pObj);

        void onUpdate() override;

        double destroyRate() const;
    private:
        EffectObj* m_pObj;
        double m_lifeTime = 58.0;
        double m_destroyTime = 2.0;
        double m_destroyMax = 2.0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Bubble::LifeTime>
    {
        using Base = MultiComponents<
            Effect::IUpdate
        >;
    };
}