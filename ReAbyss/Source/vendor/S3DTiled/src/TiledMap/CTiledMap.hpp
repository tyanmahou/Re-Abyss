#pragma once

#include "../TiledSets/TiledSets.hpp"

#include <S3DTiled/TiledLayer.hpp>
#include <S3DTiled/TiledProperty.hpp>

#include <Siv3D/Optional.hpp>
#include <Siv3D/Color.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Array.hpp>

namespace s3dTiled
{
	class CTiledMap;
	class TileSetBase;

	class CTiledMap
	{
		friend class TiledMap;
	private:
		TiledSets m_tiledSets;
		TiledProperties m_props;

		s3d::Size m_mapSize;
		s3d::Size m_tileSize;

		s3d::Optional<s3d::Color> m_backGroundColor;
		// TODO orientation
		// TODO renderorder

		s3d::Array<TiledLayer> m_layers;
		std::unordered_map<s3d::String, std::size_t> m_layerCache; // ÉåÉCÉÑÅ[Ç÷ÇÃñºëOåüçıÇO(1)Ç…Ç∑ÇÈ

	public:
		CTiledMap(const s3d::Size& mapSize, const s3d::Size& tileSize);

		s3d::Rect getRect() const;

		void setBackGroundColor(const s3d::Color& color);
		void addTileSet(std::unique_ptr<TileSetBase>&& tileSet);
		void setProps(TiledProperties&& props);
		void addLayer(const TiledLayer& layer);
	};
}