#pragma once
#include "IWorldObjectView.hpp"
#include "../MainViewFactory.hpp"
#include <Siv3D/Texture.hpp>

namespace abyss
{
	class SlimeModel;

	class SlimeView : public IWorldObjectView
	{
		s3d::Texture m_texture;
		std::weak_ptr<SlimeModel> m_pModel;

	public:
		SlimeView(std::shared_ptr<SlimeModel> pModel);

		void draw()const override;
		bool isDelete() const override;
	};
}
