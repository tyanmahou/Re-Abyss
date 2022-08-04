#include <abyss/translators/Actor/Gimmick/GimmickTranslator.hpp>

#include <abyss/modules/World/World.hpp>
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

namespace abyss::Actor::Gimmick
{
    GimmickTranslator::GimmickTranslator()
    {}

    Ref<Actor::ActorObj> GimmickTranslator::buildActor(World& world, const GimmickEntity& entity)
    {
        switch (entity.type) {
        case GimmickType::StartPos: return nullptr;
        case GimmickType::BgmChanger: return nullptr;
        default:
            break;
        }

        if (auto builder = Reflect<>::find<void(ActorObj*, const GimmickEntity&)>(
            U"abyss::Actor::Gimmick::BuilderFromEntity<{}>::Build"_fmt(static_cast<s3d::int32>(entity.type))
            )) {
            auto obj = world.create();
            builder(obj.get(), entity);
            return obj;
        }
        return nullptr;
    }
}
