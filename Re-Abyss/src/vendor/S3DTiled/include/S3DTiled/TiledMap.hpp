#pragma once
#include "TiledDef.hpp"
#include <memory>

namespace s3dTiled
{
	class ITileSet;
	class TiledLayer;

	class TiledMap
	{
		class CTiledMap;
		std::shared_ptr<CTiledMap> pImpl;
	public:
		TiledMap() = default;

		void init(const s3d::Size& mapSize, const s3d::Size& tileSize);

		void setBackGroundColor(const s3d::Color& color);
		void addLayer(const TiledLayer& layer) const;
		void addTileSet(std::unique_ptr<ITileSet>&& tileSet) const;

		void setProps(TiledProperties&& props) const;

		s3d::Optional<TiledLayer> getLayer(const s3d::String& name)const;

		bool drawLayer(const s3d::String& name, const s3d::Rect& rect) const;

		operator bool() const;
	};
}