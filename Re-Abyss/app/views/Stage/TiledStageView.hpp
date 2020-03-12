#pragma once

#include<Siv3D/Fwd.hpp>
#include<S3DTiled.hpp>

#include "base/IStageView.hpp"
#include "BackGround/BackGroundView.hpp"
#include "Bubble/BubbleGenerator.hpp"

namespace abyss
{
	class TiledStageView : public IStageView
	{
		s3dTiled::TiledMap m_map;
		BackGroundView m_bgView;
		BubbleGenerator m_bubbles;

		void drawBg(const s3d::Vec2& pos)const;
		void drawLayer(const s3d::String& layer, const s3d::RectF& rect)const;
	public:
		TiledStageView(const s3dTiled::TiledMap& map);

		void drawBack(const CameraView& camera) const override;
		void drawMiddle(const CameraView& camera) const override;
		void drawFront(const CameraView& camera) const override;
	};
}