#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Actors/base/IActorView.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss
{
	class PlayerView : public IActorView
	{
		const PlayerActor*const m_pModel;
		TexturePacker m_texture;

		void drawPlayer()const;
		void drawCharge()const;
	public:
		PlayerView(const PlayerActor*const pModel);

		void draw()const override;
	};
}
