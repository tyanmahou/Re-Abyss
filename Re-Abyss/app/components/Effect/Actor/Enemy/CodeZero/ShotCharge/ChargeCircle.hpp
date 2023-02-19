#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Effect/base/IDrawParts.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::ShotCharge
{
    class ChargeCircle :
        public IComponent,
        public IDrawParts
    {
    public:
        ChargeCircle(EffectObj* pObj, const s3d::Vec2& pos);

        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos{ 0, 0 };
        double m_radius = 0.0;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Enemy::CodeZero::ShotCharge::ChargeCircle>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}
