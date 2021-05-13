#pragma once
#include <Siv3D/Array.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Enemy
{
    class IEnemyService
    {
    public:
        virtual ~IEnemyService() = default;
        virtual const s3d::Array<std::shared_ptr<EnemyEntity>>& getEnemies() const = 0;
    };
}