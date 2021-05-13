#pragma once
#include <memory>
#include <abyss/services/Stage/base/IStageService.hpp>
#include <Emaject.hpp>

namespace abyss
{
    class StageService : public IStageService
    {
		s3d::Array<RoomEntity> m_rooms;
	public:
		INJECT_CTOR(StageService(
			std::shared_ptr<IRoomDataStore> rooms
		));

		const s3d::Array<RoomEntity>& getRooms() const override { return m_rooms; }
    };

	struct StageServiceInstaller : emaject::IInstaller
	{
		void onBinding(emaject::Container* container) const override;
	};
}