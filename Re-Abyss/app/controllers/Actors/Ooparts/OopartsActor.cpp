#include "OopartsActor.hpp"
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/components/Actors/Ooparts/PursuitCtrl.hpp>
#include <abyss/components/Actors/Ooparts/Draw.hpp>

namespace abyss::Actor::Ooparts
{
    OopartsActor::OopartsActor(IActor* parent)
    {
        this->m_isDontDestoryOnLoad = true;
        this->m_order = parent->getOrder() - 1;

        {
            // ボディと追従
            auto parentBody = parent->find<BodyModel>();
            auto forward = parentBody->getForward();
            this->attach<BodyModel>(this)
                ->initPos(parentBody->getPos() + s3d::Vec2{ forward * -20, -40 })
                .setForward(forward);

            this->attach<PursuitCtrl>(this, parentBody);
        }
        {
            // 描画
            m_view = this->attach<ViewModel<OopartsVM>>();
            this->attach<Draw>(this);
        }
    }
}
