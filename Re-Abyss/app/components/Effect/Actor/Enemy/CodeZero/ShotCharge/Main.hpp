#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Effect/base/IUpdate.hpp>
#include <abyss/modules/Effect/base/IDrawParts.hpp>
#include <abyss/utils/TimeLite/IntervalTimer.hpp>

#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Color.hpp>
#include <Siv3D/Array.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::ShotCharge
{
    class Main :
        public IComponent,
        public IUpdate,
        public IDrawParts
    {
        struct Particle
        {
            s3d::Vec2 pos;
            s3d::ColorF color;

            Particle() = default;
            Particle(const s3d::Vec2& _pos, const s3d::ColorF& _color) :
                pos(_pos),
                color(_color)
            {}
        };
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos);

        void onUpdate() override;
        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos{ 0, 0 };

        TimeLite::IntervalTimer m_particleTimer;
        s3d::Array<Particle> m_particles;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Enemy::CodeZero::ShotCharge::Main>
    {
        using Base = MultiComponents<
            Effect::IUpdate,
            Effect::IDrawParts
        >;
    };
}