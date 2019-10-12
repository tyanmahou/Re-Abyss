#pragma once
#include<domain/repository/StageRepository.hpp>

namespace abyss
{
	class World;
	class RoomModel;

	class IStageUseCase
	{
	public:
		virtual s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos) = 0;
		virtual bool init(World& world, const RoomModel& nextRoom) = 0;
		virtual bool initRoom(World& world, const RoomModel& nextRoom) = 0;
	};

	class StageUseCase : public IStageUseCase
	{
	private:
		std::unique_ptr<IStageRepository> m_stageData;

	public:
		StageUseCase(std::unique_ptr<IStageRepository>&& repository) noexcept;

		s3d::Optional<RoomModel> findRoom(const s3d::Vec2& pos) override;
		bool init(World& world, const RoomModel& nextRoom) override;
		bool initRoom(World& world, const RoomModel& nextRoom) override;
	};
}