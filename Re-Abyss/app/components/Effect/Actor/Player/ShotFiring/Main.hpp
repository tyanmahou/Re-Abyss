#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Effect/base/IDrawParts.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/ColorF.hpp>

namespace abyss::Effect::Actor::Player::ShotFiring
{
    class Main :
        public IComponent,
        public IDrawParts
    {
    public:
        Main(
            EffectObj* pObj,
            const s3d::Vec2& pos,
            double radius,
            const s3d::ColorF& color
        );

    public:
        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos;
        double m_radius;
        s3d::ColorF m_color;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Player::ShotFiring::Main>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}