#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Misc::ShockWaveDist
{
    class DistCtrl :
        public IComponent,
        public IDrawParts
    {
    public:
        DistCtrl(EffectObj* pObj, const s3d::Vec2& pos, double radius, double power, double time);

        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos;
        double m_radius;
        double m_power;
        double m_time;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Misc::ShockWaveDist::DistCtrl>
    {
        using Base = MultiComponents<
            Effect::IDrawParts
        >;
    };
}