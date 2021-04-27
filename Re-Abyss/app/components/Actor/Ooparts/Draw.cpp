#include "Draw.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Commons/Body.hpp>

#include <abyss/views/Actor/Ooparts/base/OopartsView.hpp>

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
