#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Effect::Misc::ShockWaveDist
{
    class DistCtrl :
        public IComponent,
        public IDraw
    {
    public:
        DistCtrl(EffectObj* pObj, const s3d::Vec2& pos, double radius, double power);

        bool isEnd() const override;

        void onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos;
        double m_radius;
        double m_power;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Misc::ShockWaveDist::DistCtrl>
    {
        using Base = MultiComponents<
            Effect::IDraw
        >;
    };
}