#pragma once
#include "IActorView.hpp"
#include <Siv3D/Texture.hpp>

namespace abyss
{
	class SlimeActor;

	class SlimeView : public IActorView
	{
		s3d::Texture m_texture;
		const SlimeActor* m_pModel;

	public:
		SlimeView(const SlimeActor* pModel);

		void draw()const override;
	};
}
