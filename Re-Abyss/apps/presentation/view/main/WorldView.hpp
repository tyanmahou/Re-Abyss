#pragma once
#include <Siv3D/Fwd.hpp>
#include <map>
#include <memory>
#include "object/IWorldObjectView.hpp"

namespace abyss
{
	class IWorldObjectView;

	class WorldView : public IView
	{
		using Views = std::multimap<s3d::int32, std::unique_ptr<IWorldObjectView>>;
		Views m_objectViews;

	public:
		void addView(std::unique_ptr<IWorldObjectView>&& view, s3d::int32 layer);
		void update() override;
		void draw()const override;
	};
}