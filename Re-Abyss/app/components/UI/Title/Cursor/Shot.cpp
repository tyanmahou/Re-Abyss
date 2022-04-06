#include <abyss/components/UI/Title/Cursor/Shot.hpp>

#include <Siv3D.hpp>

#include <abyss/commons/ColorDef.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/params/Actor/Player/ShotParam.hpp>
#include <abyss/components/Effect/Actor/Player/Shot/Builder.hpp>
#include <abyss/components/Effect/Actor/Player/ShotFiring/Builder.hpp>
#include <abyss/views/UI/Title/Cursor/Shot/ShotVM.hpp>

namespace abyss::UI::Title::Cursor
{
    using namespace abyss::Effect::Actor;

    Shot::Shot(UIObj* pUi, const s3d::Vec2& pos):
        m_pUi(pUi),
        m_pos(pos),
        m_view(std::make_unique<ShotVM>())
    {}

    Shot::~Shot()
    {}

    void Shot::update()
    {
        double dt = m_pUi->deltaTime();
        m_pos.x += 840 * dt;

        for ([[maybe_unused]]double carryOver : m_effectTimer.update(dt)) {
            m_pUi->getModule<Effects>()->createWorldFront<Player::Shot::Builder>(
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
    }

    void Shot::addShotFiringEffect() const
    {
        // effect
        m_pUi->getModule<Effects>()->createWorldFront<Player::ShotFiring::Builder>(
            m_pos,
            Actor::Player::ShotParam::Big::Radius,
            ColorDef::Shot::BigCharge
            );

    }
}

