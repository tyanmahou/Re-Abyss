
#include "../Parser/TiledReader.hpp"
#include "CTiledMap.hpp"

#include <S3DTiled/TiledMap.hpp>
#include <S3DTiled/TiledLayer.hpp>
#include <S3DTiled/TiledProperty.hpp>

#include <Siv3D/Color.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Array.hpp>
#include <Siv3D/TextureRegion.hpp>

using namespace s3d;

namespace s3dTiled
{
	TiledMap::TiledMap(const s3d::FilePath& path, TiledFileType fileType)
	{
		TiledReader reader(path, fileType);
		if (!reader) {
			return;
		}
		this->pImpl = reader.getTiledMap();
	}

	bool TiledMap::open(const s3d::FilePath& path, TiledFileType fileType)
	{
		TiledReader reader(path, fileType);
		if (!reader) {
			return false;
		}
		this->pImpl = reader.getTiledMap();
		return true;
	}

	const s3d::Size& TiledMap::getMapSize() const
	{
		return pImpl->m_mapSize;
	}

	const s3d::Size& TiledMap::getTileSize() const
	{
		return pImpl->m_tileSize;
	}

	s3d::Optional<TiledProperty> TiledMap::getProperty(const s3d::String& key) const
	{
		if (this->pImpl->m_props.find(key) != this->pImpl->m_props.end()) {
			return this->pImpl->m_props.at(key);
		}
		return s3d::none;
	}

	s3d::Optional<TiledLayer> TiledMap::getLayer(const s3d::String& name) const
	{
		if (pImpl->m_layerCache.find(name) == pImpl->m_layerCache.end()) {
			return s3d::none;
		}
		return pImpl->m_layers[pImpl->m_layerCache.at(name)];
	}

	s3d::TextureRegion TiledMap::getTile(GId gId) const
	{
		return pImpl->m_tiledSets.getTile(gId);
	}

	s3d::Optional<TiledProperty> TiledMap::getTileProperty(GId gId, const s3d::String& key) const
	{
		return pImpl->m_tiledSets.getProperty(gId, key);
	}

	bool TiledMap::drawLayer(const s3d::String& name, const s3d::Rect& rect) const
	{
		auto&& layer = this->getLayer(name);
		if (!layer) {

			return false;
		}
		return layer->draw(*this, rect);
	}

	void TiledMap::draw(const s3d::Rect& rect) const
	{
		pImpl->m_backGroundColor.then([&](Color bgColor) {
			rect.draw(bgColor);
		});

		for (const auto& layer : pImpl->m_layers) {
			layer.draw(*this, rect);
		}
	}

	void TiledMap::draw() const
	{
		this->draw(pImpl->getRect());
	}

	TiledMap::operator bool() const
	{
		return static_cast<bool>(pImpl);
	}
}
