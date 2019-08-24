#pragma once
#include "IWorldObjectView.hpp"
#include "../../../application/util/TexturePacker.hpp"

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
}
