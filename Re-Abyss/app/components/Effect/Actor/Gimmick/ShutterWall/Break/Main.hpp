#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Effect::Actor::Gimmick::ShutterWall::Break
{
    class PieceParts
    {
    public:
        PieceParts(const s3d::Vec2& p0, const s3d::Vec2& p1, const s3d::Vec2& p2, const s3d::Vec2& center);
        PieceParts(const s3d::Triangle& polygon, const s3d::Vec2& center);

        void update(double dt);
        void draw(const s3d::ColorF& color) const;
    private:
        s3d::Triangle m_polygon;
        s3d::Vec2 m_localPos;
        s3d::Vec2 m_velocity;

        double m_rotate = 0;
        double m_rotateSpeed = 0;

        s3d::Vec2 m_center;
    };
    class Main :
        public IComponent,
        public IUpdate,
        public IDrawParts
    {
    public:
        Main(EffectObj* pObj, const s3d::Vec2& pos);
        void onUpdate() override;
        bool onDraw(double time) override;
    private:
        EffectObj* m_pObj;
        s3d::Vec2 m_pos;
        s3d::Array<PieceParts> m_pieces;
        TimeLite::Timer m_timer;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Actor::Gimmick::ShutterWall::Break::Main>
    {
        using Base = MultiComponents<
            Effect::IUpdate,
            Effect::IDrawParts
        >;
    };
}
