#include "DrawModel.hpp"
#include <abyss/controllers/Actors/Ooparts/OopartsActor.hpp>
#include <abyss/views/Actors/Ooparts/base/OopartsVM.hpp>

namespace abyss::Ooparts
{
    DrawModel::DrawModel(OopartsActor* pActor):
        m_pActor(pActor)
    {}

    void DrawModel::onDraw() const
    {
        auto view = m_pActor->getBindedView();
        if (!view) {
            return;
        }
        view->draw();
    }

}
