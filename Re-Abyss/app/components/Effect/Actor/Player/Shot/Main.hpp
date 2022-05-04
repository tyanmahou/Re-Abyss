#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/ColorF.hpp>
#include <Siv3D/HSV.hpp>

namespace abyss::Effect::Actor::Player::Shot
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
        s3d::HSV m_hsv;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Player::Shot::Main>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}