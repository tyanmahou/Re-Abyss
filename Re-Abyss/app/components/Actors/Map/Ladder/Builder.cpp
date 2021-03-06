#include "Builder.hpp"

#include <abyss/components/Actors/Map/CommonBuilder.hpp>
#include <abyss/components/Actors/Map/Ladder/LadderProxy.hpp>

namespace abyss::Actor::Map::Ladder
{
    void Builder::Build(IActor* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size)
    {
        // 共通
        CommonBuilder::Build(pActor, col, pos, size);

        // タグ再設定
        pActor->setTag(Tag::Ladder{});

        // プロキシ
        {
            pActor->attach<LadderProxy>(pActor);
        }
   }
}