#include "Builder.hpp"

#include <abyss/components/Actor/Map/CommonBuilder.hpp>
#include <abyss/components/Actor/Commons/ReceiverData.hpp>

namespace abyss::Actor::Map::Floor
{
    void Builder::Build(ActorObj* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size)
    {
        // 共通
        CommonBuilder::Build(pActor, col, pos, size);

        // タグ再設定
        pActor->setTag(Tag::Floor{});

        // ReceiverData
        {
            pActor->attach<ReceiverData>();
        }
   }
}