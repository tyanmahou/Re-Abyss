#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/views/Actors/Enemy/Schield/Shot/ShotVM.hpp>

namespace abyss::Schield::Shot
{
    DrawModel::DrawModel(IActor* pActor) :
        m_pActor(pActor),
        m_view(std::make_unique<ShotVM>())
    {}

    void DrawModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }
    ShotVM* DrawModel::getBindedView() const
    {
        return &m_view
            ->setTime(m_pActor->getDrawTimeSec())
            .setPos(m_body->getPos());
    }

    void DrawModel::onDraw()const
    {
        auto view = this->getBindedView();
        if (!view) {
            return;
        }
        switch (m_kind) {
        case Kind::Base:
            view->draw();
            break;
        default:
            break;
        }
    }
}