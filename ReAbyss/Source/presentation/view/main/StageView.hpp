#pragma once
#include"BackGroundView.hpp"

#include<Siv3D/Fwd.hpp>
#include<S3DTiled.hpp>
namespace abyss
{
	class IStageView
	{
	public:
		virtual void drawBg(const s3d::Vec2& pos)const = 0;
		virtual void drawLayer(const s3d::String& layer, const s3d::RectF& rect)const = 0;
	};

	class TiledStageView : public IStageView
	{
		s3dTiled::TiledMap m_map;
		BackGroundView m_bgView;
	public:
		TiledStageView(const s3dTiled::TiledMap& map);


		void drawBg(const s3d::Vec2& pos)const override;
		void drawLayer(const s3d::String& layer, const s3d::RectF& rect)const override;
	};
}