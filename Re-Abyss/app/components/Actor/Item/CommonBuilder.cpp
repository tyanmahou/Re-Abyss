#include "CommonBuilder.hpp"
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/BodyUpdater.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>

namespace abyss::Actor::Item
{
    BuildOption::BuildOption():
        pos(0, 0),
        bodySize(40, 40)
    {}

    void CommonBuilder::Build(ActorObj* pActor, const BuildOption& opt)
    {
        // タグ
        pActor->setTag(Tag::Enemy{});

        // Body
        {
            pActor->attach<Body>(pActor)
                ->initPos(opt.pos)
                .setForward(Forward::Left)
                .setSize(opt.bodySize)
                ;

            pActor->attach<BodyUpdater>(pActor);
        }

        // 地形当たり
        {
            pActor->attach<MapCollider>(pActor);
        }

        // 状態管理
        {
            auto state = pActor->attach<StateCtrl>(pActor);
            if (opt.initState) {
                state->changeState(opt.initState);
            }
        }
    }
}