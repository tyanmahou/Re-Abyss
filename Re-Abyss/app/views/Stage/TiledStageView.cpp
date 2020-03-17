#include "TiledStageView.hpp"
#include <Siv3D.hpp>
#include <abyss/views/Camera/CameraView.hpp>


namespace abyss
{
	using namespace s3dTiled;

	TiledStageView::TiledStageView(const s3dTiled::TiledMap& map) :
		m_map(map)
	{
		// 背景情報取得
		map.getLayer(U"bgs")->then(
			[&](const GroupLayer& layer) {
				for (const auto& child : layer.getLayers()) {
					child.then([&](const ImageLayer& i) {
						BackGroundVM vm{
							.texture = i.getTexture(),
							.offset = i.getOffset(),
							.loop = { i.getProperty(U"loopX").value_or(false),i.getProperty(U"loopY").value_or(false) },
							.rate = { i.getProperty(U"rateX").value_or(1.0), i.getProperty(U"rateY").value_or(1.0) }
						};
						m_bgView.addBackGround(vm);
					});
				}
			}
		);
	}
	void TiledStageView::drawBg(const s3d::Vec2& pos) const
	{
		m_bgView.draw(pos);
	}
	void TiledStageView::drawLayer(const s3d::String& layer, const s3d::RectF& rect) const
	{
		m_map.drawLayer(layer, rect);
	}

	void TiledStageView::drawBack(const CameraView& camera) const
	{
		auto&& screen = camera.screenRegion();

		m_waveShader.apply(camera, [&] {

			// 背景
			this->drawBg(camera.getCameraPos());
		});
		// back obj
		this->drawLayer(U"back", screen);

	}
	void TiledStageView::drawMiddle(const CameraView& camera) const
	{
		auto&& screen = camera.screenRegion();

		// map
		this->drawLayer(U"map", screen);
		// door
		this->drawLayer(U"door", screen);	
	}
	void TiledStageView::drawFront(const CameraView& camera) const
	{
		auto&& screen = camera.screenRegion();
		// front obj
		this->drawLayer(U"front", screen);

		m_bubbles.draw(camera.getCameraPos());
	}
}