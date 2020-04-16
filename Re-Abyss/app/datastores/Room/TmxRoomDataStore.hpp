#pragma once
#include <abyss/datastores/Room/base/IRoomDataStore.hpp>
#include <abyss/datastores/base/TmxDataStore.hpp>
namespace abyss
{
    class TmxRoomDataStore :
        public TmxDataStore,
        public IRoomDataStore
    {
    public:
        using TmxDataStore::TmxDataStore;

        s3d::Array<RoomEntity> select()const override;
    };
}