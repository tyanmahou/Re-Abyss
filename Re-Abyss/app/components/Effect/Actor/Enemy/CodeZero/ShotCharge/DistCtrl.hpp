#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Effect/base/IDrawParts.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::ShotCharge
{
    class DistCtrl :
        public IComponent,
        public IDrawParts
    {
    public:
        DistCtrl(EffectObj* pObj, const s3d::Vec2& pos);

        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos{ 0, 0 };
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Enemy::CodeZero::ShotCharge::DistCtrl>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}
