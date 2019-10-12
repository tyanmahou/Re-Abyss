#pragma once
#include "IActorView.hpp"
#include <Siv3D/Texture.hpp>

namespace abyss
{
	class PlayerShotActor;

	class PlayerShotView : public IActorView
	{
		s3d::Texture m_texture;
		const PlayerShotActor* m_pModel;

	public:
		PlayerShotView(const PlayerShotActor* pModel);

		void start()override;
		void draw()const override;
	};
}
