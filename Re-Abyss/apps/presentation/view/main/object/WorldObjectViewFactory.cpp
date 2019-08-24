#include "WorldObjectViewFactory.hpp"

#include "PlayerView.hpp"
#include "PlayerShotView.hpp"

namespace abyss
{
	std::unique_ptr<IWorldObjectView> WorldObjectViewFactory::createViewFromModel(const std::shared_ptr<WorldObject>&)const
	{
		return nullptr;
	}
	std::unique_ptr<IWorldObjectView> WorldObjectViewFactory::createViewFromModel(const std::shared_ptr<PlayerModel>& model)const
	{
		auto view = std::make_unique<PlayerView>(model);
		return view;
	}
	std::unique_ptr<IWorldObjectView> WorldObjectViewFactory::createViewFromModel(const std::shared_ptr<PlayerShotModel>& model)const
	{
		auto view = std::make_unique<PlayerShotView>(model);
		return view;
	}
}