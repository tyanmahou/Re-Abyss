#pragma once

#include<S3DTiled/TiledTypes.hpp>

#include<Siv3D/Fwd.hpp>
#include<Siv3D/Optional.hpp>

#include<memory>

namespace s3dTiled
{
	class CTiledMap;

	/// <summary>
	/// Tiledì«Ç›çûÇ›
	/// </summary>
	class TiledReader
	{
	private:

		class CTiledReader;

		std::shared_ptr<CTiledReader> pImpl;

	public:
		TiledReader();

		explicit TiledReader(const s3d::FilePath& path, TiledFileType fileType = TiledFileType::Unspecified);

		bool open(const s3d::FilePath& path, TiledFileType fileType = TiledFileType::Unspecified);

		operator bool() const;

		std::shared_ptr<CTiledMap> getTiledMap() const;
	};
}

