#include "../include/S3DTiled/TiledMap.hpp"

#include "../include/S3DTiled/TiledSets.hpp"
#include "../include/S3DTiled/TiledProperty.hpp"
#include "../include/S3DTiled/TiledLayer.hpp"

#include <Siv3D/Color.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Array.hpp>

using namespace s3d;

namespace s3dTiled
{
	class TiledMap::CTiledMap
	{
		friend class TiledMap;
	private:
		TiledSets m_tiledSets;
		TiledProperties m_props;

		Size m_size;
		Optional<Color> m_backGroundColor;
		// TODO orientation
		// TODO renderorder

		s3d::Array<TiledLayer> m_layers;
		std::unordered_map<String, std::size_t> m_layerCache; // ÉåÉCÉÑÅ[Ç÷ÇÃñºëOåüçıÇO(1)Ç…Ç∑ÇÈ
	public:
		CTiledMap(const s3d::Size& mapSize, const s3d::Size& tileSize):
			m_size(mapSize)
		{
			m_tiledSets.setTileSize(tileSize);
		}
	};


	void TiledMap::init(const s3d::Size& mapSize, const s3d::Size& tileSize)
	{
		pImpl = std::make_shared<CTiledMap>(mapSize, tileSize);
	}

	void TiledMap::setBackGroundColor(const s3d::Color& color)
	{
		pImpl->m_backGroundColor = color;
	}

	void TiledMap::addLayer(const TiledLayer& layer) const
	{
		std::size_t index = pImpl->m_layers.size();
		pImpl->m_layerCache[layer.getName()] = index;

		pImpl->m_layers.push_back(layer);
	}

	void TiledMap::addTileSet(std::unique_ptr<ITileSet>&& tileSet) const
	{
		pImpl->m_tiledSets.addTileSet(std::move(tileSet));
	}

	void TiledMap::setProps(TiledProperties&& props) const
	{
		pImpl->m_props = std::move(props);
	}

	s3d::Optional<TiledLayer> TiledMap::getLayer(const s3d::String& name) const
	{
		if (pImpl->m_layerCache.find(name) == pImpl->m_layerCache.end()) {
			return s3d::none;
		}
		return pImpl->m_layers[pImpl->m_layerCache.at(name)];
	}

	bool TiledMap::drawLayer(const s3d::String& name, const s3d::Rect& rect) const
	{
		auto&& layer = this->getLayer(name);
		if (!layer) {

			return false;
		}
		return layer->draw(pImpl->m_tiledSets, rect);
	}

	TiledMap::operator bool() const
	{
		return static_cast<bool>(pImpl);
	}
}
