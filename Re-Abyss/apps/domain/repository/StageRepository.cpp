#include "StageRepository.hpp"

namespace abyss
{
	StageRepository::StageRepository(const s3d::FilePath& path):
		m_dataStore(std::make_unique<TiledStageDataStore>(path)),
		m_rooms(m_dataStore->getRoomEntity()),
		m_maps(m_dataStore->getMapEntity()),
		m_doors(m_dataStore->getDoorEntity()),
		m_bgs(m_dataStore->getBackGroundEntity())
	{}
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
	const s3d::Array<BackGroundEntity>& StageRepository::getBgs() const
	{
		return m_bgs;
	}
}