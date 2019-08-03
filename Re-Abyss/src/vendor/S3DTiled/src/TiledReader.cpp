#include "../include/S3DTiled/TiledReader.hpp"
#include "../include/S3DTiled/TiledMap.hpp"

#include "Parser/TiledParser.hpp"

#include <Siv3D/String.hpp>
#include <Siv3D/FileSystem.hpp>
using namespace s3d;

namespace s3dTiled
{
	class TiledReader::CTiledReader
	{
		friend TiledReader;
	private:
		TiledMap m_map;

		bool open(const FilePath& path, TiledFileType fileType)
		{
			if (fileType == TiledFileType::Tmx || FileSystem::Extension(path) == L"tmx") {
				return ParseTmx(path, m_map);
			}
			else if (fileType == TiledFileType::Json || FileSystem::Extension(path) == L"json") {
				// TODO Json Parse
			}
			return false;
		}
	public:
		CTiledReader() = default;

		CTiledReader(const FilePath& path, TiledFileType fileType)
		{
			this->open(path, fileType);
		}
	};

	TiledReader::TiledReader():
		pImpl(std::make_shared<CTiledReader>())
	{}

	TiledReader::TiledReader(const FilePath & path, TiledFileType fileType) :
		pImpl(std::make_shared<CTiledReader>(path, fileType))
	{}

	bool TiledReader::open(const FilePath& path, TiledFileType fileType)
	{
		return pImpl->open(path, fileType);
	}

	TiledReader::operator bool() const
	{
		return pImpl->m_map;
	}
	const TiledMap& TiledReader::getTiledMap() const
	{
		return pImpl->m_map;
	}
}
