#pragma once

#include <S3DTiled/TiledTypes.hpp>

#include<memory>

namespace s3dTiled
{
	class TileSetBase;

	class TiledSets
	{
		class CTiledSets;
		std::shared_ptr<CTiledSets> pImpl;
	public:
		TiledSets();

		void addTileSet(std::unique_ptr<TileSetBase>&& tileSet) const;
		s3d::TextureRegion getTile(GId gId) const;

		s3d::Optional<TiledProperty> getProperty(GId gId, const s3d::String& key) const;
	};
}