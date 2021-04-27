#pragma once
#include <memory>
#include <Siv3D/Array.hpp>
#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>

namespace abyss
{
    class IEnemyDataStore
    {
    public:
        virtual ~IEnemyDataStore() = default;

        virtual s3d::Array<std::shared_ptr<EnemyEntity>> select()const = 0;
    };
}