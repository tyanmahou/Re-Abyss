#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/views/Actors/Enemy/RollingTako/RollingTakoVM.hpp>

namespace abyss::RollingTako
{
    DrawModel::DrawModel(IActor* pActor) :
        m_pActor(pActor),
        m_view(std::make_unique<RollingTakoVM>())
    {

    }
    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_hp = m_pActor->find<HPModel>();
    }
    RollingTakoVM* DrawModel::getBindedView() const
    {
        return &m_view->setTime(m_pActor->getDrawTimeSec())
            .setPos(m_body->getPos())
            .setForward(m_body->getForward())
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
        case Kind::Wait:
            view->drawWait();
            break;
        case Kind::Run:
            view->drawRun();
            break;
        default:
            break;
        }
    }
}