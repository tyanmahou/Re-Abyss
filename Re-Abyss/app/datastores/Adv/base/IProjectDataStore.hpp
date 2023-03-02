#pragma once
#include <abyss/entities/Adv/CharaEntity.hpp>

namespace abyss::Adv
{
    class IProjectDataStore
    {
    public:
        virtual ~IProjectDataStore() = default;

        virtual s3d::Array<CharaEntity> selectCharas() const = 0;
    };
}
