#include "MainViewFactory.hpp"

#include <presentation/view/main/MainView.hpp>

namespace abyss
{

	//MainViewFactory::MainViewFactory(MainView* view):
	//	m_pMainView(view)
	//{
	//}
	//std::unique_ptr<IWorldObjectView> MainViewFactory::createViewFromModel(const std::shared_ptr<WorldObject>&)const
	//{
	//	return nullptr;
	//}

	//std::unique_ptr<IWorldObjectView> MainViewFactory::createViewFromModel(const std::shared_ptr<PlayerShotModel>& model)const
	//{
	//	auto view = std::make_unique<PlayerShotView>(model);
	//	return view;
	//}

	MainViewFactory::MainViewFactory(MainView* view) :
		m_pMainView(view)
	{
	}

	//std::unique_ptr<IWorldObjectView> MainViewFactory::createViewFromModel(const std::shared_ptr<SlimeModel>& model)const
	//{
	//	auto view = std::make_unique<SlimeView>(model);
	//	return view;
	//}
}