#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/views/Actors/Enemy/Schield/SchieldVM.hpp>

namespace abyss::Schield
{
    DrawModel::DrawModel(IActor* pActor) :
        m_pActor(pActor),
        m_view(std::make_unique<SchieldVM>())
    {}

    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_hp = m_pActor->find<HPModel>();
    }
    SchieldVM* DrawModel::getBindedView() const
    {
        return &m_view->setTime(m_pActor->getDrawTimeSec())
            .setPos(m_body->getPos())
            .setForward(m_body->getForward())
            .setIsDamaging(m_hp->isInInvincibleTime());
    }

    void DrawModel::onDraw()const
    {
        auto view = this->getBindedView();
        if (!view) {
            return;
        }
        switch (m_kind) {
        case Kind::ToWait:
            view->drawToWait(m_transitionTime);
            break;
        case Kind::Wait:
            view->drawWait();
            break;
        case Kind::ToAttackPlus:
            view->drawToAttackPlus(m_transitionTime);
            break;
        case Kind::AttackPlus:
            view->drawAttackPlus();
            break;
        case Kind::ToAttackCross:
            view->drawToAttackCross(m_transitionTime);
            break;
        case Kind::AttackCross:
            view->drawAttackCross();
            break;
        default:
            break;
        }
    }
}