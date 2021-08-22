#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/components/Effect/Bubble/BubbleKind.hpp>
#include <Siv3D.hpp>

namespace abyss::Effect::Bubble
{
    class Main :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        Main(EffectObj* pObj);

        void onUpdate() override;
        void onDraw(double time) override;

        bool isEnd() const override
        {
            return m_isEnd;
        }

        bool checkEnd();
    private:
        s3d::Vec2 parallaxPos() const;
        s3d::Circle drawCircle(double time) const;
        bool isInValidRange(const s3d::Vec2& pos) const;
    private:
        EffectObj* m_pObj;
        bool m_isEnd = false;

        BubbleKind m_kind;
        double m_maxRadius;

        s3d::Vec2 m_basePos{0, 0};
        s3d::Vec2 m_pos{ 0, 0 };
        s3d::Vec2 m_velocity{0, 0};
        double m_deflection = 0;
        s3d::Vec2 m_parallax{ 1.0, 1.0 };
        ColorF m_color;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Bubble::Main>
    {
        using Base = MultiComponents<
            Effect::IUpdate,
            Effect::IDraw
        >;
    };
}