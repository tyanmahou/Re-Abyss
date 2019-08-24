#pragma once

#include "TiledTypes.hpp"

#include <memory>

namespace s3dTiled
{
	class TiledLayer;
	class CTiledMap;

	class TiledMap
	{
		std::shared_ptr<CTiledMap> pImpl;
	public:
		TiledMap() = default;

		TiledMap(const s3d::FilePath& path, TiledFileType fileType = TiledFileType::Unspecified);

		bool open(const s3d::FilePath& path, TiledFileType fileType = TiledFileType::Unspecified);

		const s3d::Size& getMapSize() const;
		const s3d::Size& getTileSize() const;

		s3d::Optional<TiledProperty> getProperty(const s3d::String& key) const;

		s3d::Optional<TiledLayer> getLayer(const s3d::String& name)const;

		s3d::TextureRegion getTile(GId gId) const;
		s3d::Optional<TiledProperty> getTileProperty(GId gId, const s3d::String& key) const;

		void draw(const s3d::Rect& rect) const;
		void draw() const;
		bool drawLayer(const s3d::String& name, const s3d::Rect& rect) const;

		operator bool() const;
	};
}