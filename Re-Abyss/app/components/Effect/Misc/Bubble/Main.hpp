#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Effect/base/IDrawParts.hpp>
#include <abyss/components/Effect/Common/LifeTime.hpp>
#include <abyss/components/Effect/Misc/Bubble/BubbleKind.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Color.hpp>

namespace abyss::Effect::Misc::Bubble
{
    class Main :
        public IComponent,
        public IUpdate,
        public IDrawParts
    {
    public:
        struct Param
        {
            BubbleKind kind;
            double maxRadius;

            s3d::Vec2 basePos;
            s3d::Vec2 velocity;
            double deflection;
            s3d::Vec2 parallax;
            s3d::ColorF color;
        };
    public:
        Main(EffectObj* pObj);

        void onStart() override;
        void onUpdate() override;
        bool onDraw(double time) override;

        bool checkEnd();

        Main& setParam(const Param& param)
        {
            m_kind = param.kind;
            m_maxRadius = param.maxRadius;
            m_basePos = param.basePos;
            m_velocity = param.velocity;
            m_deflection = param.deflection;
            m_parallax = param.parallax;
            m_color = param.color;
            return *this;
        }
        Main& setArea(const s3d::RectF& area)
        {
            m_area = area;
            return *this;
        }
        bool isInArea(const s3d::RectF& area) const;
    private:
        s3d::Vec2 parallaxPos() const;
        s3d::Circle drawCircle() const;
        bool isInValidRange(const s3d::Vec2& pos) const;
    private:
        EffectObj* m_pObj;
        bool m_isEnd = false;

        BubbleKind m_kind;
        double m_radius = 0.0;
        double m_maxRadius = 1.0;

        s3d::Vec2 m_basePos{0, 0};
        s3d::Vec2 m_pos{ 0, 0 };
        s3d::Vec2 m_velocity{0, 0};
        double m_deflection = 0;
        s3d::Vec2 m_parallax{ 1.0, 1.0 };
        s3d::ColorF m_color;
        s3d::RectF m_area;

        Ref<LifeTime> m_lifeTime;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Misc::Bubble::Main>
    {
        using Base = MultiComponents<
            Effect::IUpdate,
            Effect::IDrawParts
        >;
    };
}