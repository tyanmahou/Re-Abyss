#include "OopartsActor.hpp"
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Ooparts/PursuitModel.hpp>
#include <abyss/models/Actors/Ooparts/DrawModel.hpp>
namespace abyss::Ooparts
{
    OopartsActor::OopartsActor(IActor* parent)
    {
        this->m_isDontDestoryOnLoad = true;
        this->m_order = parent->getOrder() - 1;

        {
            // ボディと追従
            auto parentBody = parent->find<BodyModel>();
            auto forward = parentBody->getForward();
            (m_body = this->attach<BodyModel>(this))
                ->initPos(parentBody->getPos() + s3d::Vec2{ forward * -20, -40 })
                .setForward(forward);

            this->attach<PursuitModel>(this, parentBody);
        }
        {
            // 描画
            this->attach<DrawModel>(this);
        }
    }

}
