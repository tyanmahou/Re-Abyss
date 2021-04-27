#include "Shot.hpp"
#include <Siv3D.hpp>

#include <abyss/commons/ColorDef.hpp>
#include <abyss/params/Actor/Player/ShotParam.hpp>
#include <abyss/views/Actor/Player/Shot/ShotEffect.hpp>
#include <abyss/views/Cycle/Title/Cursor/Shot/ShotVM.hpp>

namespace abyss::Cycle::Title::Cursor
{
    Shot::Shot(const s3d::Vec2& pos):
        m_pos(pos),
        m_view(std::make_unique<ShotVM>()),
        m_effectTimer(0.033, true)
    {}

    Shot::~Shot()
    {}

    void Shot::update()
    {
        m_pos.x += 840 * Scene::DeltaTime();

        if (m_effectTimer.update()) {
            m_effect.add<Actor::Player::Shot::ShotEffect>(
                m_pos,
                Actor::Player::ShotParam::Big::Radius,
                ColorDef::Shot::BigCharge
                );
        }
    }

    void Shot::draw() const
    {
        m_view
            ->setPos(m_pos)
            .setTime(Scene::Time())
            .draw();
        m_effect.update();
    }
    void Shot::addShotFiringEffect()
    {
        m_effect.add<Actor::Player::Shot::ShotFiringEffect>(
            m_pos,
            Actor::Player::ShotParam::Big::Radius,
            ColorDef::Shot::BigCharge
            );
    }
}

