#pragma once
#include "IWorldObjectView.hpp"
#include <application/util/TexturePacker.hpp>
#include "../MainViewFactory.hpp"
namespace abyss
{
	class PlayerActor;

	class PlayerView : public IWorldObjectView
	{
		TexturePacker m_texture;
		std::weak_ptr<PlayerActor> m_pPlayer;

		void drawPlayer()const;
		void drawCharge()const;
	public:
		PlayerView(std::shared_ptr<PlayerActor> pPlayer);

		void draw()const override;
		bool isDelete() const override;
	};
}
