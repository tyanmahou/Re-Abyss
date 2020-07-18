#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/views/Actors/Enemy/LaunShark/LaunSharkVM.hpp>

namespace abyss::LaunShark
{
    DrawModel::DrawModel(IActor* pActor) :
        m_pActor(pActor),
        m_view(std::make_unique<LaunSharkVM>())
    {}

    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_hp = m_pActor->find<HPModel>();
    }
    LaunSharkVM* DrawModel::getBindedView() const
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
        case Kind::Swim:
            view->drawSwim();
            break;
        case Kind::LaunShark:
            view->drawLauncher(m_transitionTime);
            break;
        case Kind::Attack:
            view->drawAttack();
            break;
        default:
            break;
        }
    }
}