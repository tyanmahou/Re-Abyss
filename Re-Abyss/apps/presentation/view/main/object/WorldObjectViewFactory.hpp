#pragma once
#include<memory>

namespace abyss
{
	class WorldObject;
	class IWorldObjectView;

	class PlayerModel;
	class PlayerShotModel;

	class IWorldObjectViewFactory
	{
	public:
		virtual std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<WorldObject>&)const = 0;
		virtual std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<PlayerModel>&)const = 0;
		virtual std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<PlayerShotModel>&)const = 0;
	};


	class WorldObjectViewFactory : public IWorldObjectViewFactory
	{
	public:
		std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<WorldObject>&)const override;
		std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<PlayerModel>& model)const override;
		std::unique_ptr<IWorldObjectView> createViewFromModel(const std::shared_ptr<PlayerShotModel>& model)const override;
	};
}