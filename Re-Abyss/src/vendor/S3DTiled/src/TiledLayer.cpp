#include "../include/S3DTiled/TiledLayer.hpp"
#include "../include/S3DTiled/TiledSets.hpp"

#include <Siv3D/TextureRegion.hpp>
using namespace s3d;
namespace s3dTiled
{
	TiledLayer::TiledLayer(std::shared_ptr<ILayer> layer):
		pImpl(layer)
	{}

	bool TiledLayer::draw(const TiledSets& tileSets, const s3d::Rect& rect) const
	{
		return pImpl->draw(tileSets, rect);
	}

	LayerType TiledLayer::getType() const
	{
		if (!this->pImpl) {
			return LayerType::None;
		}
		return this->pImpl->getType();
	}

	const s3d::String& TiledLayer::getName() const
	{
		return this->pImpl->getName();
	}

	// ITiledLayer

	void ILayer::setVisible(bool visible)
	{
		this->m_visible = visible;
	}
	void ILayer::setProps(TiledProperties&& props)
	{
		this->m_props = std::move(props);
	}
	void ILayer::setName(const s3d::String& name)
	{
		this->m_name = name;
	}
	const s3d::String& ILayer::getName() const
	{
		return m_name;
	}
	void ILayer::setOffset(const s3d::Vec2& offset)
	{
		this->m_offset = offset;
	}

	// ImageLayer

	void ImageLayer::setTexture(s3d::Texture texture)
	{
		m_texture = texture;
	}

	bool ImageLayer::draw(const TiledSets&, const Rect& rect) const
	{
		if (!m_visible) {
			return false;
		}
		if (!RectF(m_offset, m_texture.size).intersects(rect)) {
			// ”ÍˆÍŠO
			return false;
		}
		m_texture.draw(m_offset);

		return true;
	}

	LayerType ImageLayer::getType() const
	{
		return LayerType::ImageLayer;
	}

	// TileLayer

	void TileLayer::setGrid(Grid<GId>&& grid)
	{
		this->m_gIds = std::move(grid);
	}

	bool TileLayer::draw(const TiledSets& tileSets, const Rect& rect) const
	{
		if (!m_visible) {
			return false;
		}

		Vec2 tileSize = tileSets.getTileSize();

		GId xStart = static_cast<GId>(rect.x / tileSize.x);
		GId yStart = static_cast<GId>(rect.y / tileSize.y);

		GId xEnd = xStart + static_cast<GId>(rect.w / tileSize.x);
		GId yEnd = yStart + static_cast<GId>(rect.h / tileSize.y);


		for (GId y = yStart; y < yEnd; ++y) {
			for (GId x = xStart; x < xEnd; ++x) {
				GId gId = m_gIds[y][x];
				if (gId == 0) {
					continue;
				}
				auto&& texture = tileSets.getTile(gId);
				Vec2 pos = { x * tileSize.x, y * tileSize.y };
				if (tileSets.needAxisAdjust(gId)) {
					// axis‚Ì’²®
					pos.y -= (texture.size.y - tileSize.y);
				}
				texture.draw(pos);
			}
		}
		return true;
	}

	LayerType TileLayer::getType() const
	{
		return LayerType::TileLayer;
	}

	// ObjectGroup

	void ObjectGroup::addObject(TiledObject && obj)
	{
		this->m_objects.push_back(std::move(obj));
	}

	bool ObjectGroup::draw(const TiledSets& /*tileSets*/, const Rect& /*rect*/) const
	{
		if (!m_visible) {
			return false;
		}
		// TODO
		return true;
	}

	LayerType ObjectGroup::getType() const
	{
		return LayerType::ObjectGroup;
	}
}