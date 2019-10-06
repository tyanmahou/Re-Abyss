#include "StageView.hpp"
#include <Siv3D.hpp>

namespace
{

}
namespace abyss
{
	using namespace s3dTiled;

	TiledStageView::TiledStageView(const s3dTiled::TiledMap& map) :
		m_map(map)
	{
		// ”wŒiî•ñŽæ“¾
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
}