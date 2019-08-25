#pragma once
#include<domain/repository/StageRepository.hpp>

namespace abyss
{
	class WorldUseCase;
	class RoomModel;

	class StageUseCase
	{
	private:
		StageRepository m_stageData;

	public:
		StageUseCase(const s3d::FilePath& path);

		s3d::Optional<RoomModel> init(WorldUseCase& world);
		s3d::Optional<RoomModel> initRoom(WorldUseCase& world);

		const s3d::Array<BackGroundEntity>& getBgs() const;
	};
}