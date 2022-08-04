#include <abyss/components/Actor/Gimmick/EventTrigger/Builder.hpp>
#include <abyss/components/Actor/Gimmick/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Gimmick/EventTrigger/Main.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    void Builder::Build(ActorObj* pActor, const EventTriggerEntity& entity)
    {
        Build(pActor, entity.event);
    }
    void Builder::Build(ActorObj* pActor, const s3d::FilePath& path)
    {
        pActor->attach<Main>(pActor, path);
    }
}

namespace abyss::Actor::Gimmick
{
    template struct BuilderFromEntity<GimmickType::EventTrigger>;
    template<>
    void BuilderFromEntity<GimmickType::EventTrigger>::Build(ActorObj* pActor, const GimmickEntity& entity)
    {
        EventTrigger::Builder::Build(pActor, static_cast<const EventTriggerEntity&>(entity));
    }
}
