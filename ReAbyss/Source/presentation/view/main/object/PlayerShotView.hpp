#pragma once
#include "IWorldObjectView.hpp"
#include <Siv3D/Texture.hpp>

namespace abyss
{
	class PlayerShotActor;

	class PlayerShotView : public IWorldObjectView
	{
		s3d::Texture m_texture;
		std::weak_ptr<PlayerShotActor> m_pModel;

	public:
		PlayerShotView(std::shared_ptr<PlayerShotActor> pModel);

		void start()override;
		void update() override;
		void draw()const override;
		bool isDelete() const override;
	};
}
