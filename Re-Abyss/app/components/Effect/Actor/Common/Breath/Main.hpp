#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Actor::Breath
{
    class Main :
        public IComponent,
        public IDrawParts
    {
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos);
        ~Main();

    public:
        bool onDraw(double time) override;

    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Breath::Main>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}