#pragma once
#include<memory>
namespace abyss
{
	class WorldObject;
	class IWorldObjectView;
	class ICameraWorkView;
	class MainView;


	class MainViewFactory
	{
		MainView* m_pMainView;

	public:
		MainViewFactory(MainView*);

		template<class T>
		std::unique_ptr<IWorldObjectView>  createFromModel(const std::shared_ptr<T>&) const
		{
			return nullptr;
		}

		template<class T>
		std::unique_ptr<ICameraWorkView> createFromCameraWork(const std::shared_ptr<T>& )const
		{
			return nullptr;
		}
	};
}