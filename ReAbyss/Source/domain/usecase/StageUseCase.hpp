#pragma once
#include<domain/repository/StageRepository.hpp>
#include<domain/usecase/StageObservable.hpp>

namespace abyss
{
	class WorldUseCase;
	class RoomModel;

	class StageUseCase : public StageObservable
	{
	private:
		StageRepository m_stageData;

	public:
		StageUseCase();

		void load(const s3d::FilePath& path);

		s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos);

		bool init(WorldUseCase& world, const RoomModel& nextRoom);
		bool initRoom(WorldUseCase& world, const RoomModel& nextRoom);
	};
}