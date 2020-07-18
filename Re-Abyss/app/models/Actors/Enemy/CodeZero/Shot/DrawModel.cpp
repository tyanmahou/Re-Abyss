#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/ScaleModel.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Shot/ShotVM.hpp>

namespace abyss::CodeZero::Shot
{
    DrawModel::DrawModel(IActor* pActor) :
        m_pActor(pActor),
        m_view(std::make_unique<ShotVM>())
    {}

    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
        m_scale = m_pActor->find<ScaleModel>();
    }
    ShotVM* DrawModel::getBindedView() const
    {
        return &m_view->setTime(m_pActor->getDrawTimeSec())
            .setPos(m_body->getPos())
            .setScale(m_scale->get());
    }

    void DrawModel::onDraw()const
    {
        auto view = this->getBindedView();
        if (!view) {
            return;
        }
        switch (m_motion) {
        case Motion::Base:
            view->draw();
            break;
        case Motion::Charge:
            view->drawCharge();
            view->draw();
        default:
            break;
        }
    }
}