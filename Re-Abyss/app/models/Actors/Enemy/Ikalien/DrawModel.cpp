#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/views/Actors/Enemy/Ikalien/IkalienVM.hpp>

namespace abyss::Ikalien
{
    DrawModel::DrawModel(IActor* pActor) :
        m_pActor(pActor),
        m_view(std::make_unique<IkalienVM>())
    {}
    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_hp = m_pActor->find<HPModel>();
        m_rotate = m_pActor->find<RotateModel>();
    }
    IkalienVM* DrawModel::getBindedView() const
    {
        return &m_view->setTime(m_pActor->getDrawTimeSec())
            .setPos(m_body->getPos())
            .setVelocity(m_body->getVelocity())
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
            break;
        case Kind::Pursuit:
            view->drawPursuit();
            break;
        case Kind::Swim:
            view->drawSwim();
            break;
        default:
            break;
        }
    }
}