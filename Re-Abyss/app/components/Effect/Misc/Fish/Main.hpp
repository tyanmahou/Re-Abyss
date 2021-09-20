#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/components/Effect/base/IUpdate.hpp>
#include <abyss/components/Effect/base/IDraw.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Effect/Common/LifeTime.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/RectF.hpp>

namespace abyss::Effect::Misc::Fish
{
    class FishVM;

    class Main :
        public IComponent,
        public IUpdate,
        public IDraw
    {
    public:
        Main(EffectObj* pObj, s3d::int32 fishId);

        void onStart() override;
        void onUpdate() override;
        bool onDraw(double time) override;

        Main& setBasePos(const s3d::Vec2& pos)
        {
            m_basePos = pos;
            return *this;
        }

        Main& setParallax(const s3d::Vec2& parallax)
        {
            m_parallax = parallax;
            return *this;
        }
        Main& setVelocity(const s3d::Vec2& velocity);
        Main& setScale(double scale);

        Main& setColor(const s3d::ColorF& color)
        {
            m_color = color;
            return *this;
        }

        bool checkEnd();

        bool isInArea(const s3d::RectF& area) const;
    private:
        s3d::Vec2 parallaxPos() const;
        s3d::RectF viewRect() const;
        bool isInValidRange() const;
    private:
        EffectObj* m_pObj;
        bool m_isEnd = false;
        s3d::Vec2 m_basePos{0, 0};
        s3d::Vec2 m_parallax{ 1.0, 1.0 };
        s3d::Vec2 m_velocity{0, 0};
        s3d::ColorF m_color{};
        std::unique_ptr<FishVM> m_view;
        Ref<LifeTime> m_lifeTime;
    };
}

namespace abyss
{
    template<>
    struct ComponentTree<Effect::Misc::Fish::Main>
    {
        using Base = MultiComponents<
            Effect::IUpdate,
            Effect::IDraw
        >;
    };
}