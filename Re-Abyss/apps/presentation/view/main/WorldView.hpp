#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/Effect.hpp>

#include <memory>
#include "object/IWorldObjectView.hpp"

namespace abyss
{
	class IWorldObjectView;

	class WorldView : public IView
	{
		using Views = s3d::Array<std::unique_ptr<IWorldObjectView>>;
		Views m_objectViews;

		s3d::Effect m_effect;
	public:
		void addView(std::unique_ptr<IWorldObjectView>&& view);
		void update() override;
		void draw()const override;

		s3d::Effect& getEffect();
	};
}