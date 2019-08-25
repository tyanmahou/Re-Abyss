#include "StageRepository.hpp"

namespace abyss
{
	StageRepository::StageRepository() 
	{}
	std::unique_ptr<IStageDataStore> StageRepository::load(const s3d::FilePath& path)
	{
		auto dataStore = std::make_unique<TiledStageDataStore>(path);
		m_rooms = dataStore->getRoomEntity();
		m_maps = dataStore->getMapEntity();
		m_doors = dataStore->getDoorEntity();
		return dataStore;
	}
	const s3d::Array<RoomEntity>& StageRepository::getRooms() const
	{
		return m_rooms;
	}
	const s3d::Array<MapEntity>& StageRepository::getMaps() const
	{
		return m_maps;
	}
	const s3d::Array<DoorEntity>& StageRepository::getDoors() const
	{
		return m_doors;
	}
}