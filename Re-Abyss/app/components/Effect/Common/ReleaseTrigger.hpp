#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Effect/base/IUpdate.hpp>

namespace abyss::Effect
{
    /// <summary>
    /// トリガー破棄
    /// </summary>
    class ReleaseTrigger :
        public IComponent,
        public IUpdate
    {
    public:
        ReleaseTrigger(EffectObj* pObj);

        void onUpdate() override;

        ReleaseTrigger& setTrigger(const std::function<bool()>& trigger)
        {
            m_trigger = trigger;
            return *this;
        }
    private:
        EffectObj* m_pObj;
        std::function<bool()> m_trigger;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::ReleaseTrigger>
    {
        using Base = MultiComponents<
            Effect::IUpdate
        >;
    };
}