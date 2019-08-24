#pragma once
#include "../view/main/MainView.hpp"

#include <domain/usecase/WorldUseCase.hpp>

#include <memory>
#include <Siv3D/Fwd.hpp>

namespace abyss
{
	class IMainPresenter
	{};

	class MainPresenter : public IMainPresenter
	{
		std::shared_ptr<IMainView> m_view;
		
		WorldUseCase m_worldUseCase;
	public:

		MainPresenter(std::shared_ptr<IMainView> view);
	};
}