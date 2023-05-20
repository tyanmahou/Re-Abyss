#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/TimeLite/IntervalTimer.hpp>
#include <abyss/params/UI/Title/CursorParam.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Title::Cursor
{
    class ShotVM;

    class Shot
    {
    public:
        Shot(UIObj* pUi);
        ~Shot();

        void update();
        void draw() const;

        void addShotFiringEffect() const;

        void setPos(const s3d::Vec2& pos, const s3d::Vec2& offset = CursorParam::ViewParam::ShotOffset);
    private:
        UIObj* m_pUi;
        s3d::Vec2 m_pos;
        std::unique_ptr<ShotVM> m_view;

        TimeLite::IntervalTimer m_effectTimer{0.033};
    };
}
