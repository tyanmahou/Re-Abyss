#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>

namespace abyss::Effect::Actor::Gimmick::ShutterWall::Break
{
    class Main :
        public IComponent,
        public IDrawParts
    {
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos);
        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Gimmick::ShutterWall::Break::Main>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}
