#include "CommonBuilder.hpp"
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Common/Colliders/CircleCollider.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Item/ItemCollision.hpp>

namespace abyss::Actor::Item
{
    BuildOption::BuildOption():
        pos(0, 0),
        bodySize(40, 40),
        audioSettingGroupPath(U"Item/item.aase")
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
                .initSize(opt.bodySize)
                .initPivot(opt.bodyPivot)
                .setMaxVelocityY(20.0)
                ;

            pActor->attach<BodyUpdater>(pActor);
        }

        // 地形当たり
        {
            pActor->attach<MapCollider>(pActor);
        }

        // アイテム当たり
        {
            pActor->attach<ItemCollision>(pActor);

            pActor->attach<CircleCollider>(pActor)
                ->setRadius(opt.m_colliderRadius.value_or((opt.bodySize.x + opt.bodySize.y) / 4.0))
                ;
        }
        // 音源
        {
            pActor->attach<AudioSource>(pActor)
                ->load(opt.audioSettingGroupPath);
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