#pragma once
#include<Siv3D/Fwd.hpp>
#include<Siv3D/Optional.hpp>
#include<Siv3D/IReader.hpp>
#include<memory>

namespace s3dTiled
{
	class TiledLayer;
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

		template <class Reader, class = std::enable_if_t<std::is_base_of<s3d::IReader, Reader>::value>>
		explicit TiledReader(Reader&& reader, const s3d::FilePath& parentPath , TiledFileType fileType = TiledFileType::Tmx)
			: TiledReader()
		{
			open(std::move(reader), parentPath, fileType);
		}

		explicit TiledReader(const std::shared_ptr<s3d::IReader>& reader, const s3d::FilePath& parentPath , TiledFileType fileType = TiledFileType::Tmx);

		bool open(const s3d::FilePath& path, TiledFileType fileType = TiledFileType::Unspecified);

		bool open(const std::shared_ptr<s3d::IReader>& reader, const s3d::FilePath& parentPath , TiledFileType fileType = TiledFileType::Tmx);

		template <class Reader, class = std::enable_if_t<std::is_base_of<s3d::IReader, Reader>::value>>
		bool open(Reader&& reader, const s3d::FilePath& parentPath = L"", TiledFileType fileType = TiledFileType::Tmx)
		{
			return open(std::make_shared<Reader>(std::move(reader)), parentPath, fileType);
		}

		s3d::Optional<TiledLayer> getLayer(const s3d::String& name)const;

		bool drawLayer(const s3d::String& name, const s3d::Rect& rect) const;
	};
}

