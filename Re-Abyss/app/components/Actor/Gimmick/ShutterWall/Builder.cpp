#include <abyss/components/Actor/Gimmick/ShutterWall/Builder.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Gimmick/BuilderFromEntity.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    void Builder::Build(ActorObj* pActor, const ShutterWallEntity& entity)
    {
    }

}

namespace abyss::Actor::Gimmick
{
    template struct BuilderFromEntity<GimmickType::ShutterWall>;
    template<>
    void BuilderFromEntity<GimmickType::EventTrigger>::Build(ActorObj* pActor, const GimmickEntity& entity)
    {
        ShutterWall::Builder::Build(pActor, static_cast<const ShutterWallEntity&>(entity));
    }
}
