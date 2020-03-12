#pragma once

#include <Siv3D/Texture.hpp>

#include <abyss/commons/Fwd.hpp>
#include <abyss/views/Actors/base/IActorView.hpp>

namespace abyss
{
	class PlayerShotView : public IActorView
	{
		const PlayerShotActor* const m_pModel;

		s3d::Texture m_texture;
	public:
		PlayerShotView(const PlayerShotActor*const pModel);

		void start()override;
		void draw()const override;
	};
}
