#include "OopartsCtrl.hpp"
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/Ooparts/OopartsActor.hpp>
#include <abyss/controllers/Actors/Ooparts/Xto/XtoActor.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/Ooparts/PursuitCtrl.hpp>

namespace abyss::Actor::Player
{
    OopartsCtrl::OopartsCtrl(IActor* pActor):
        m_pActor(pActor)
    {}
    void OopartsCtrl::setup()
    {
        m_attackCtrl = m_pActor->find<AttackCtrl>();
        m_body = m_pActor->find<BodyModel>();
    }
    void OopartsCtrl::onStart()
    {
        std::shared_ptr<Ooparts::OopartsActor> main = m_pActor->getModule<World>()->create<Ooparts::Xto::XtoActor>(m_pActor);
        this->setMain(main);
    }
    OopartsCtrl& Player::OopartsCtrl::setMain(const Ref<Ooparts::OopartsActor> & main)
    {
        m_mainOoparts = main;
        return *this;
    }
    void OopartsCtrl::onLastUpdate()
    {
        if (!m_attackCtrl || !m_mainOoparts) {
            return;
        }
        if (m_attackCtrl->isAttacking()) {
            m_mainOoparts->setActive(false);
            m_mainOoparts->find<Ooparts::PursuitCtrl>()
                ->setLocalPos(s3d::Vec2{ 30 * m_body->getForward(), -1 })
                .setIsPursuit(false);
        } else {
            m_mainOoparts->setActive(true);
            m_mainOoparts->find<Ooparts::PursuitCtrl>()
                ->setIsPursuit(true);
        }
    }
}
