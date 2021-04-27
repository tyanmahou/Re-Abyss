#include "Draw.hpp"
#include <abyss/modules/Actors/base/ActorObj.hpp>

#include <abyss/components/Actors/Commons/Body.hpp>

#include <abyss/views/Actors/Ooparts/base/OopartsView.hpp>

namespace abyss::Actor::Ooparts
{
    Draw::Draw(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void Draw::onStart()
    {
        m_view = m_pActor->find<ViewCtrl<OopartsView>>();
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
