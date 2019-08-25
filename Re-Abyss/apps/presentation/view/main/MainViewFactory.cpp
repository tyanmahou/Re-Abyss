#include "MainViewFactory.hpp"

#include <presentation/view/main/object/PlayerView.hpp>
#include <presentation/view/main/object/SlimeView.hpp>
#include <presentation/view/main/object/PlayerShotView.hpp>
#include <presentation/view/main/CameraWorkView.hpp>
#include <presentation/view/main/MainView.hpp>

namespace abyss
{
	MainViewFactory::MainViewFactory(MainView* view):
		m_pMainView(view)
	{
	}
	std::unique_ptr<IWorldObjectView> MainViewFactory::createViewFromModel(const std::shared_ptr<WorldObject>&)const
	{
		return nullptr;
	}
	std::unique_ptr<IWorldObjectView> MainViewFactory::createViewFromModel(const std::shared_ptr<PlayerModel>& model)const
	{
		auto view = std::make_unique<PlayerView>(model);
		return view;
	}
	std::unique_ptr<IWorldObjectView> MainViewFactory::createViewFromModel(const std::shared_ptr<PlayerShotModel>& model)const
	{
		auto view = std::make_unique<PlayerShotView>(model);
		return view;
	}
	std::unique_ptr<ICameraWorkView> MainViewFactory::createViewFromModel(const std::shared_ptr<DoorCameraWork>& model)const
	{
		auto view = std::make_unique<DoorCameraWorkView>(m_pMainView->getCameraView(), model);
		return view;
	}
	std::unique_ptr<IWorldObjectView> MainViewFactory::createViewFromModel(const std::shared_ptr<SlimeModel>& model)const
	{
		auto view = std::make_unique<SlimeView>(model);
		return view;
	}
}