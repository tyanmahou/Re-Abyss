#pragma once
#include<memory>

namespace abyss
{
	class MainView;
	class WorldObject;
	class IWorldObjectView;

	class PlayerModel;
	class PlayerShotModel;

	class ICameraWorkView;
	class DoorCameraWork;

	class IMainViewFactory
	{
	public:
		virtual std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<WorldObject>&)const = 0;
		virtual std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<PlayerModel>&)const = 0;
		virtual std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<PlayerShotModel>&)const = 0;

		// camera work
		virtual std::unique_ptr<ICameraWorkView> createViewFromModel(const std::shared_ptr<DoorCameraWork>&)const = 0;
	};


	class MainViewFactory : public IMainViewFactory
	{
		MainView* m_pMainView;

	public:
		MainViewFactory(MainView*);
		std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<WorldObject>&)const override;
		std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<PlayerModel>& model)const override;
		std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<PlayerShotModel>& model)const override;

		std::unique_ptr<ICameraWorkView> createViewFromModel(const std::shared_ptr<DoorCameraWork>& model)const override;
	};
}