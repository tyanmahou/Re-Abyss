#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Effect::Actor::Item::Recovery
{
    class LocationCtrl :
        public IComponent,
        public IUpdate
    {
    public:
        LocationCtrl(EffectObj* pObj, const Ref<abyss::Actor::ILocator>& locator);

        const s3d::Vec2& getPos() const;
    public:
        void onUpdate() override;
    private:
        EffectObj* m_pObj;
        Ref<abyss::Actor::ILocator> m_locator;
        s3d::Vec2 m_pos;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Item::Recovery::LocationCtrl>
    {
        using Base = MultiComponents<
            Effect::IUpdate
        >;
    };
}