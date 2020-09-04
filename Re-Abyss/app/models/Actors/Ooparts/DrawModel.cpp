#include "DrawModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

#include <abyss/models/Actors/Commons/BodyModel.hpp>

#include <abyss/views/Actors/Ooparts/base/OopartsVM.hpp>

namespace abyss::Actor::Ooparts
{
    DrawModel::DrawModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void DrawModel::setup()
    {
        m_view = m_pActor->find<ViewModel<OopartsVM>>();
    }

    void DrawModel::onDraw() const
    {
        auto view = m_view->getBindedView();
        if (!view) {
            return;
        }
        view->draw();
    }

}
