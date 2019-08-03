#pragma once
#include<Siv3D/Fwd.hpp>
#include<Siv3D/Optional.hpp>
#include<memory>

namespace s3dTiled
{
	class TiledMap;
	/// <summary>
	/// Tiled�̃t�@�C���`��
	/// </summary>
	enum class TiledFileType
	{
		Unspecified,
		Tmx,
		Json
	};

	/// <summary>
	/// Tiled�ǂݍ���
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

