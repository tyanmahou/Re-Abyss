#include <abyss/services/Room/RoomService.hpp>
#include <abyss/datastores/Room/base/IRoomDataStore.hpp>

namespace abyss
{
    RoomService::RoomService(std::shared_ptr<IRoomDataStore> rooms):
        m_rooms(rooms->select())
    {}

    const s3d::Array<RoomEntity>& RoomService::getRooms() const
    {
        return m_rooms;
    }

    void RoomServiceInstaller::onBinding(emaject::Container* container) const
    {
        container->bind<IRoomService>()
            .to<RoomService>()
            .asCache();
    }
}
