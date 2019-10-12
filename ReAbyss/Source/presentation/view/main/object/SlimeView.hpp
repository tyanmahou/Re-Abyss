#pragma once
#include "IWorldObjectView.hpp"
#include <Siv3D/Texture.hpp>

namespace abyss
{
	class SlimeActor;

	class SlimeView : public IWorldObjectView
	{
		s3d::Texture m_texture;
		std::weak_ptr<SlimeActor> m_pModel;

	public:
		SlimeView(std::shared_ptr<SlimeActor> pModel);

		void draw()const override;
		bool isDelete() const override;
	};
}
