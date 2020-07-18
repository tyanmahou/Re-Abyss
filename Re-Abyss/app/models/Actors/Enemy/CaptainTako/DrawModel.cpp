#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/views/Actors/Enemy/CaptainTako/CpatainTakoVM.hpp>

namespace abyss::CaptainTako
{
    DrawModel::DrawModel(IActor* pActor) :
        m_pActor(pActor),
        m_view(std::make_unique<CaptainTakoVM>())
    {}

    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_hp = m_pActor->find<HPModel>();
    }
    CaptainTakoVM* DrawModel::getBindedView() const
    {
        return &m_view
            ->setTime(m_pActor->getDrawTimeSec())
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
        case Kind::Wait:
            view->drawWait();
            break;
        case Kind::Charge:
            view->drawCharge(m_chargeTime);
            break;
        default:
            break;
        }
    }
}