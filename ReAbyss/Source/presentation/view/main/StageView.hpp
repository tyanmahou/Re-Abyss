#pragma once
#include<Siv3D/Fwd.hpp>
#include<S3DTiled.hpp>

namespace abyss
{
	class IStageView
	{
	public:
		virtual void drawLayer(const s3d::String& layer, const s3d::RectF& rect)const = 0;
	};

	class TiledStageView : public IStageView
	{
		s3dTiled::TiledMap m_map;
	public:
		TiledStageView(const s3dTiled::TiledMap& map);
		void drawLayer(const s3d::String& layer, const s3d::RectF& rect)const override;
	};
}