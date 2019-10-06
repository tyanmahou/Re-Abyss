#pragma once
#include "IWorldObjectView.hpp"
#include <Siv3D/Texture.hpp>

namespace abyss
{
	class PlayerShotModel;

	class PlayerShotView : public IWorldObjectView
	{
		s3d::Texture m_texture;
		std::weak_ptr<PlayerShotModel> m_pModel;

	public:
		PlayerShotView(std::shared_ptr<PlayerShotModel> pModel);

		void start()override;
		void update() override;
		void draw()const override;
		bool isDelete() const override;
	};
}
