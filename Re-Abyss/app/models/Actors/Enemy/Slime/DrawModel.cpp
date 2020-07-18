#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/views/Actors/Enemy/Slime/SlimeVM.hpp>

namespace abyss::Slime
{
    DrawModel::DrawModel(IActor* pActor):
        m_pActor(pActor),
        m_view(std::make_unique<SlimeVM>())
    {

    }
    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_hp = m_pActor->find<HPModel>();
    }
    SlimeVM* DrawModel::getBindedView() const
    {
        return &m_view->setTime(m_pActor->getDrawTimeSec())
            .setForward(m_body->getForward())
            .setPos(m_body->getPos())
            .setVelocity(m_body->getVelocity())
            .setIsDamaging(m_hp->isInInvincibleTime())
            ;
    }

    void DrawModel::onDraw()const
    {
        auto view = this->getBindedView();
        if (!view) {
            return;
        }
        switch (m_kind) {
        case Kind::Walk:
            view->drawWalk();
            break;
        case Kind::Jump:
            view->drawJump();
            break;
        default:
            break;
        }
    }
}