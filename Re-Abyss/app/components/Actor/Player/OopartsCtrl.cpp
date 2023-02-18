#include <abyss/components/Actor/Player/OopartsCtrl.hpp>

#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Ooparts/Xto/Builder.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
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

        std::shared_ptr<ActorObj> main = m_pActor->getModule<Actors>()->create<Ooparts::Xto::Builder>(m_pActor);
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

            // 非表示
            m_mainOoparts->find<VModel>()->setVisible(false);

            // 手元に移動
            m_mainOoparts->find<Ooparts::PursuitCtrl>()
                ->setLocalPos(s3d::Vec2{ 30 * m_body->getForward().signH(), -1})
                .setIsPursuit(false);


        } else {
            // 表示
            m_mainOoparts->find<VModel>()->setVisible(true);
            m_mainOoparts->find<Ooparts::PursuitCtrl>()
                ->setIsPursuit(true);
        }
    }
}
