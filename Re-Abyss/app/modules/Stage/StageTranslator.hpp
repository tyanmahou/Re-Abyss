#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss
{
    namespace Decor::Map
    {
        class TileMapData;
    }

    struct StageTranslator
    {
        static Ref<Actor::ActorObj> Build(Actors& actors, const Actor::Enemy::EnemyEntity& entity);
        static Ref<Actor::ActorObj> Build(Actors& actors, const Actor::Gimmick::GimmickEntity& entity);
        static Ref<Actor::ActorObj> Build(Actors& actors, const Actor::Item::ItemEntity& entity);
        static Ref<Actor::ActorObj> Build(Actors& actors, const Actor::Land::LandEntity& entity);

        static Ref<Decor::DecorObj> Build(Decors& decor, const Decor::DecorEntity& entity);
        static Ref<Decor::DecorObj> Build(Decors& decor, const Decor::Map::TileMapData& tileMap);
    };
}
