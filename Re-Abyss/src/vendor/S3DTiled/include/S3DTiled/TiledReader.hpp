#pragma once
#include<Siv3D/Fwd.hpp>
#include<Siv3D/Optional.hpp>
#include<memory>

namespace s3dTiled
{
	class TiledMap;
	/// <summary>
	/// Tiledのファイル形式
	/// </summary>
	enum class TiledFileType
	{
		Unspecified,
		Tmx,
		Json
	};

	/// <summary>
	/// Tiled読み込み
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

		const TiledMap& getTiledMap() const;
	};
}

