#pragma once

#include <domain/usecase/StageUseCase.hpp>
#include <domain/usecase/CameraUseCase.hpp>

#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class IMainPresenter
	{
	public:
		virtual ~IMainPresenter() = default;
		virtual void update() = 0;

		virtual Observable<void(const std::shared_ptr<DoorCameraWork>&)>& onStartDoorCameraWork() = 0;
	};

	class MainPresenter : public IMainPresenter
	{
		std::unique_ptr<IStageUseCase> m_stageUseCase;
		CameraUseCase m_cameraUseCase;

	public:

		MainPresenter();
		void update();
		Observable<void(const std::shared_ptr<DoorCameraWork>&)>& onStartDoorCameraWork() override;
	};
}