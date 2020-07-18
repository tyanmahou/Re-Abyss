#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/views/Actors/Enemy/LaunShark/Shot/ShotVM.hpp>

namespace abyss::LaunShark::Shot
{
    DrawModel::DrawModel(IActor* pActor) :
        m_pActor(pActor),
        m_view(std::make_unique<ShotVM>())
    {}

    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_rotate = m_pActor->find<RotateModel>();
        m_hp = m_pActor->find<HPModel>();
    }
    ShotVM* DrawModel::getBindedView() const
    {
        return &m_view->setTime(m_pActor->getDrawTimeSec())
            .setPos(m_body->getPos())
            .setRotate(m_rotate->getRotate())
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
        case Kind::Pursuit:
        case Kind::Firinged:
            view->drawFiringed();
            break;
        default:
            break;
        }
    }
}