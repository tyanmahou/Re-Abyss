#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/TimeLite/IntervalTimer.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Title::Cursor
{
    class ShotVM;

    class Shot
    {
    public:
        Shot(UIObj* pUi, const s3d::Vec2& pos);
        ~Shot();

        void update();
        void draw() const;

        void addShotFiringEffect() const;
    private:
        UIObj* m_pUi;
        s3d::Vec2 m_pos;
        std::unique_ptr<ShotVM> m_view;

        TimeLite::IntervalTimer m_effectTimer{0.033};
    };
}