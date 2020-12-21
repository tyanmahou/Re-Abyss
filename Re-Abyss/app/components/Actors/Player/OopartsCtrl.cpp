#include "OopartsCtrl.hpp"
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>

#include <abyss/components/Actors/Ooparts/Xto/Builder.hpp>

#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Player/AttackCtrl.hpp>
#include <abyss/components/Actors/Ooparts/PursuitCtrl.hpp>

namespace abyss::Actor::Player
{
    OopartsCtrl::OopartsCtrl(IActor* pActor):
        m_pActor(pActor)
    {}
    void OopartsCtrl::onStart()
    {
        m_attackCtrl = m_pActor->find<AttackCtrl>();
        m_body = m_pActor->find<Body>();

        std::shared_ptr<IActor> main = m_pActor->getModule<World>()->create<Ooparts::Xto::Builder>(m_pActor);
        this->setMain(main);
    }
    OopartsCtrl& Player::OopartsCtrl::setMain(const Ref<IActor> & main)
    {
        if (m_mainOoparts) {
            m_mainOoparts->destroy();
        }
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
