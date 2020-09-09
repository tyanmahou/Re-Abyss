#include "Draw.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

#include <abyss/components/Actors/Commons/Body.hpp>

#include <abyss/views/Actors/Ooparts/base/OopartsVM.hpp>

namespace abyss::Actor::Ooparts
{
    Draw::Draw(IActor* pActor):
        m_pActor(pActor)
    {}

    void Draw::setup()
    {
        m_view = m_pActor->find<ViewCtrl<OopartsVM>>();
    }

    void Draw::onDraw() const
    {
        auto view = m_view->getBindedView();
        if (!view) {
            return;
        }
        view->draw();
    }

}
