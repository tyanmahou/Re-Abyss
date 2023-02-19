#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Effect/base/IDrawParts.hpp>

#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::NegaPosi
{
    class Main :
        public IComponent,
        public IDrawParts
    {
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos);

        void onStart() override;
        void onEnd() override;

        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos{ 0, 0 };
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Enemy::CodeZero::NegaPosi::Main>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}
