#pragma once
#include <memory>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Title::Cursor
{
    class ShotVM;

    class Shot
    {
        s3d::Vec2 m_pos;
        std::unique_ptr<ShotVM> m_view;
    public:
        Shot(const s3d::Vec2& pos);
        ~Shot();

        void update();
        void draw() const;
    };
}