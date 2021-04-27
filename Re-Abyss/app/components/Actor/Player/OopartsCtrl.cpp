#include "OopartsCtrl.hpp"
#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Ooparts/Xto/Builder.hpp>

#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Player/AttackCtrl.hpp>
#include <abyss/components/Actor/Ooparts/PursuitCtrl.hpp>

namespace abyss::Actor::Player
{
    OopartsCtrl::OopartsCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void OopartsCtrl::onStart()
    {
        m_attackCtrl = m_pActor->find<AttackCtrl>();
        m_body = m_pActor->find<Body>();

        std::shared_ptr<ActorObj> main = m_pActor->getModule<World>()->create<Ooparts::Xto::Builder>(m_pActor);
        this->setMain(main);
    }
    OopartsCtrl& Player::OopartsCtrl::setMain(const Ref<ActorObj> & main)
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
