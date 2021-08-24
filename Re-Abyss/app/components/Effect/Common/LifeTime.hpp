#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>

namespace abyss::Effect
{
    /// <summary>
    /// 寿命
    /// </summary>
    class LifeTime :
        public IComponent,
        public IUpdate
    {
    public:
        LifeTime(EffectObj* pObj);

        void onUpdate() override;

        LifeTime& setTime(double lifeTime, double destroyTime = 0.0)
        {
            m_lifeTime = lifeTime;
            m_destroyTime = destroyTime;
            m_destroyMax = destroyTime;
            return *this;
        }
        double destroyRate() const;
    private:
        EffectObj* m_pObj;
        double m_lifeTime = 10.0;
        double m_destroyTime = 0.0;
        double m_destroyMax = 0.0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::LifeTime>
    {
        using Base = MultiComponents<
            Effect::IUpdate
        >;
    };
}