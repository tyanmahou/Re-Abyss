#include <abyss/components/Actor/Gimmick/CodeZeroBack/Builder.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Gimmick/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Gimmick/CodeZeroBack/Main.hpp>
#include <abyss/entities/Actor/Gimmick/CodeZeroBackEntity.hpp>

namespace abyss::Actor::Gimmick::CodeZeroBack
{
    void Builder::Build(ActorObj* pActor, const CodeZeroBackEntity& entity)
    {
        pActor->attach<Main>(pActor, entity.pos)
            ->setLayer(DrawLayer::DecorBack)
            .setOrder(DrawOrder::DecorBack::MostFront);
    }
}
namespace abyss::Actor::Gimmick
{
    template struct BuilderFromEntity<GimmickType::CodeZeroBack>;
    template<>
    void BuilderFromEntity<GimmickType::CodeZeroBack>::Build(ActorObj* pActor, const GimmickEntity& entity)
    {
        CodeZeroBack::Builder::Build(pActor, static_cast<const CodeZeroBackEntity&>(entity));
    }
}
