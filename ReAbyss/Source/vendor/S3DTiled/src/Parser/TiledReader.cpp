#include "TiledReader.hpp"
#include "TiledParser.hpp"
#include "../TiledMap/CTiledMap.hpp"

#include <S3DTiled/TiledMap.hpp>

#include <Siv3D/String.hpp>
#include <Siv3D/FileSystem.hpp>

using namespace s3d;

namespace s3dTiled
{
	class TiledReader::CTiledReader
	{
		friend TiledReader;
	private:
		std::shared_ptr<CTiledMap> m_map;

		bool open(const FilePath& path, TiledFileType fileType)
		{
			if (fileType == TiledFileType::Tmx || FileSystem::Extension(path) == U"tmx") {
				m_map = ParseTmx(path);
			}
			else if (fileType == TiledFileType::Json || FileSystem::Extension(path) == U"json") {
				// TODO Json Parse
			}
			return static_cast<bool>(m_map);
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
		return static_cast<bool>(pImpl->m_map);
	}
	std::shared_ptr<CTiledMap> TiledReader::getTiledMap() const
	{
		return pImpl->m_map;
	}
}
