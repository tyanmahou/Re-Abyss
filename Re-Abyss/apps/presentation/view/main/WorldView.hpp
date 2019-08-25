#pragma once
#include <Siv3D/Fwd.hpp>
#include <Siv3D/Array.hpp>
#include <map>
#include <memory>
#include "object/IWorldObjectView.hpp"

namespace abyss
{
	class IWorldObjectView;

	class WorldView : public IView
	{
		using Views = s3d::Array<std::unique_ptr<IWorldObjectView>>;
		Views m_objectViews;
	public:
		void addView(std::unique_ptr<IWorldObjectView>&& view);
		void update() override;
		void draw()const override;
	};
}