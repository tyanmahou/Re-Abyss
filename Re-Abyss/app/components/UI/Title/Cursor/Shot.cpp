#include "Shot.hpp"
#include <Siv3D.hpp>

#include <abyss/commons/ColorDef.hpp>
#include <abyss/params/Actor/Player/ShotParam.hpp>
#include <abyss/views/Actor/Player/Shot/ShotEffect.hpp>
#include <abyss/views/UI/Title/Cursor/Shot/ShotVM.hpp>

namespace abyss::UI::Title::Cursor
{
    Shot::Shot(const s3d::Vec2& pos):
        m_pos(pos),
        m_view(std::make_unique<ShotVM>())
    {}

    Shot::~Shot()
    {}

    void Shot::update()
    {
        m_pos.x += 840 * Scene::DeltaTime();
    }

    void Shot::draw() const
    {
        m_view
            ->setPos(m_pos)
            .setTime(Scene::Time())
            .draw();
    }
}

