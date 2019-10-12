#pragma once
#include "IActorView.hpp"
#include <application/util/TexturePacker.hpp>
namespace abyss
{
	class PlayerActor;

	class PlayerView : public IActorView
	{
		TexturePacker m_texture;
		const PlayerActor* m_pModel;

		void drawPlayer()const;
		void drawCharge()const;
	public:
		PlayerView(const PlayerActor* pModel);

		void draw()const override;
	};
}
