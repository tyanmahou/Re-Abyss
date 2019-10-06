#include "StageView.hpp"
#include <Siv3D.hpp>

namespace abyss
{
	TiledStageView::TiledStageView(const s3dTiled::TiledMap& map):
		m_map(map)
	{}
	void TiledStageView::drawLayer(const s3d::String& layer, const s3d::RectF& rect) const
	{
		m_map.drawLayer(layer, rect);
	}
}
