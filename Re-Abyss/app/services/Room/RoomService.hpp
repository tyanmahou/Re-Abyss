#pragma once

#include <abyss/services/Room/base/IRoomService.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class IRoomDataStore;

    class RoomService : public IRoomService
    {
    public:
        INJECT_CTOR(RoomService(
            std::shared_ptr<IRoomDataStore> rooms
        ));
        const s3d::Array<RoomEntity>& getRooms() const override;
    private:
        s3d::Array<RoomEntity> m_rooms;
    };

    struct RoomServiceInstaller : emaject::IInstaller
    {
        void onBinding(emaject::Container* container) const override;
    };
}