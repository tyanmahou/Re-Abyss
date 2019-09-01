#pragma once
#include "IWorldObjectView.hpp"
#include <application/util/TexturePacker.hpp>
#include "../MainViewFactory.hpp"
namespace abyss
{
	class PlayerModel;

	class PlayerView : public IWorldObjectView
	{
		TexturePacker m_texture;
		std::weak_ptr<PlayerModel> m_pPlayer;

		void drawPlayer()const;
		void drawCharge()const;
	public:
		PlayerView(std::shared_ptr<PlayerModel> pPlayer);

		void draw()const override;
		bool isDelete() const override;
	};

	template<>
	inline std::unique_ptr<IWorldObjectView> MainViewFactory::createFromModel<PlayerModel>(const std::shared_ptr<PlayerModel>& model)const
	{
		auto view = std::make_unique<PlayerView>(model);
		return view;
	}
}
