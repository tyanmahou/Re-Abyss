#include "OopartsCtrlModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/Ooparts/OopartsActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

#include <abyss/models/Actors/Player/AttackCtrlModel.hpp>
#include <abyss/models/Actors/Ooparts/PursuitModel.hpp>
#include <abyss/models/Actors/Ooparts/DrawModel.hpp>

namespace abyss::Player
{
    OopartsCtrlModel::OopartsCtrlModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void OopartsCtrlModel::setup()
    {
        m_attackCtrl = m_pActor->find<AttackCtrlModel>();
        m_body = m_pActor->find<BodyModel>();
    }
    OopartsCtrlModel& Player::OopartsCtrlModel::setMain(const Ref<Ooparts::OopartsActor> & main)
    {
        m_mainOoparts = main;
        return *this;
    }
    void OopartsCtrlModel::onLastUpdate()
    {
        if (!m_attackCtrl || !m_mainOoparts) {
            return;
        }
        if (m_attackCtrl->isAttacking()) {
            m_mainOoparts->setActive(false);
            m_mainOoparts->find<Ooparts::PursuitModel>()
                ->setLocalPos(s3d::Vec2{ 30 * m_body->getForward(), -1 })
                .setIsPursuit(false);
        } else {
            m_mainOoparts->setActive(true);
            m_mainOoparts->find<Ooparts::PursuitModel>()
                ->setIsPursuit(true);
        }
    }
}
