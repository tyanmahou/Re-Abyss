#include <S3DTiled/TiledMap.hpp>
#include <S3DTiled/TiledLayer.hpp>

#include <Siv3D/TextureRegion.hpp>
#include <Siv3D/TexturedQuad.hpp>
#include <Siv3D/Math.hpp>
#include <Siv3D/Mat3x2.hpp>

using namespace s3d;
namespace s3dTiled
{
	TiledLayer::TiledLayer(std::shared_ptr<TiledLayerBase> layer) :
		pImpl(layer)
	{}

	bool TiledLayer::draw(const TiledMap& map, const s3d::Rect& rect) const
	{
		return pImpl->draw(map, rect);
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

	s3d::Optional<TiledProperty> TiledLayer::getProperty(const s3d::String& key) const
	{
		return pImpl->getProperty(key);
	}

	void TiledLayer::setVisible(bool visible)
	{
		pImpl->setVisible(visible);
	}

	bool TiledLayer::getVisible() const
	{
		return pImpl->getVisible();
	}

	bool TiledLayer::then(std::function<void(const ImageLayer&)> callback) const
	{
		if (pImpl->getType() != LayerType::ImageLayer) {
			return false;
		}
		if (auto layer = dynamic_cast<ImageLayer*>(pImpl.get())) {
			callback(*layer);
			return true;
		}
		return false;
	}

	bool TiledLayer::then(std::function<void(const TileLayer&)> callback) const
	{
		if (pImpl->getType() != LayerType::TileLayer) {
			return false;
		}
		if (auto layer = dynamic_cast<TileLayer*>(pImpl.get())) {
			callback(*layer);
			return true;
		}
		return false;
	}

	bool TiledLayer::then(std::function<void(const ObjectGroup&)> callback) const
	{
		if (pImpl->getType() != LayerType::ObjectGroup) {
			return false;
		}
		if (auto layer = dynamic_cast<ObjectGroup*>(pImpl.get())) {
			callback(*layer);
			return true;
		}
		return false;
	}
	// TiledLayerBase

	void TiledLayerBase::setVisible(bool visible)
	{
		this->m_visible = visible;
	}
	bool TiledLayerBase::getVisible() const
	{
		return m_visible;
	}
	void TiledLayerBase::setProps(TiledProperties&& props)
	{
		this->m_props = std::move(props);
	}
	s3d::Optional<TiledProperty> TiledLayerBase::getProperty(const s3d::String& key) const
	{
		if (this->m_props.find(key) != this->m_props.end()) {
			return this->m_props.at(key);
		}
		return s3d::none;
	}
	void TiledLayerBase::setName(const s3d::String& name)
	{
		this->m_name = name;
	}
	const s3d::String& TiledLayerBase::getName() const
	{
		return m_name;
	}
	void TiledLayerBase::setOffset(const s3d::Vec2& offset)
	{
		this->m_offset = offset;
	}

	// ImageLayer

	void ImageLayer::setTexture(s3d::Texture texture)
	{
		m_texture = texture;
	}

	bool ImageLayer::draw(const TiledMap& /*map*/, const Rect& rect) const
	{
		if (!m_visible) {
			return false;
		}
		if (!RectF(m_offset, m_texture.size).intersects(rect)) {
			// 範囲外
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

	const s3d::Grid<GId>& TileLayer::getGrid() const
	{
		return m_gIds;
	}

	bool TileLayer::draw(const TiledMap& map, const Rect& rect) const
	{
		if (!m_visible) {
			return false;
		}

		Vec2 tileSize = map.getTileSize();

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
				auto&& texture = map.getTile(gId);
				Vec2 pos = { x * tileSize.x, y * tileSize.y };
				// 座標の調整
				pos.y -= (texture.size.y - tileSize.y);
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

	const s3d::Array<TiledObject>& ObjectGroup::getObjects() const
	{
		return m_objects;
	}

	bool ObjectGroup::draw(const TiledMap& map, const Rect & rect) const
	{
		if (!m_visible) {
			return false;
		}
		for (auto&& obj : m_objects) {
			if (obj.gId) {
				auto&& texture = map.getTile(obj.gId.value());

				// 座標の調整
				Vec2 pos = obj.pos;
				Vec2 offset{ texture.size.x / 2, -+texture.size.y / 2 };
				pos += offset;
				double rad = s3d::Math::Radians(obj.rotation);
				pos = Mat3x2::Rotate(rad, obj.pos).transform(pos);

				auto&& textureQuad = texture.rotate(rad);
				auto drawRegion = textureQuad.quad.movedBy(pos - textureQuad.center);
				if (!rect.intersects(drawRegion)) {
					// 範囲外
					continue;
				}
				textureQuad.drawAt(pos);
			}
		}
		return true;
	}

	LayerType ObjectGroup::getType() const
	{
		return LayerType::ObjectGroup;
	}
}