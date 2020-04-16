#pragma once
#include <abyss/entities/Room/RoomEntity.hpp>
#include <Siv3D/Array.hpp>

namespace abyss
{
    class IRoomDataStore
    {
    public:
        virtual ~IRoomDataStore() = default;

        virtual s3d::Array<RoomEntity> select()const = 0;
    };
}