#pragma once
#include "../view/main/MainView.hpp"

#include <domain/usecase/WorldUseCase.hpp>
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
	};

	class MainPresenter : public IMainPresenter
	{
		std::shared_ptr<IMainView> m_view;
		
		WorldUseCase m_worldUseCase;
		StageUseCase m_stageUseCase;
		CameraUseCase m_cameraUseCase;

	public:

		MainPresenter(std::shared_ptr<IMainView> view);
		void update();
	};
}