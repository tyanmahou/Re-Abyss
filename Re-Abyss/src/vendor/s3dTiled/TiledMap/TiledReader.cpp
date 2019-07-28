#include "TiledReader.hpp"
#include "TiledSets.hpp"
#include "TiledProperty.hpp"
#include "TiledLayer.hpp"
#include "TiledUtil.hpp"

#include<Siv3D.hpp>

namespace {




}
namespace s3dTiled
{
	class TiledReader::CTiledReader
	{
		friend TiledReader;
	private:
		bool loadXML(XMLReader xml, const FilePath& parentPath)
		{
			auto root = xml.root();

			// mapê›íË
			m_size.x = Parse<int32>(root.attribute(L"width").value_or(L"0"));
			m_size.y = Parse<int32>(root.attribute(L"height").value_or(L"0"));
			m_tileSets.setTileSize({
				Parse<int32>(root.attribute(L"tilewidth").value_or(L"0")),
				Parse<int32>(root.attribute(L"tileheight").value_or(L"0"))
			});
			if (auto && col = root.attribute(L"backgroundcolor")) {
				
				m_backGroundColor = ParseTiledColor(root.attribute(L"backgroundcolor").value());
			}

			for (auto elm = root.firstChild(); elm; elm = elm.nextSibling()) {
				ParseProps(elm, this->m_props, parentPath);

				if (elm.name() == L"tileset") {
					m_tileSets.pushTileSet(elm, parentPath);
				}

				if (elm.name() == L"imagelayer" || elm.name() == L"layer" || elm.name() == L"objectgroup") {
					auto&& name = elm.attribute(L"name").value_or(L"");
					this->m_layers[name] = TiledLayer(elm, parentPath);
				}
			}
			return true;
		}
		bool loadJSON(JSONReader, const FilePath&)
		{
			// TODO
			return true;
		}

		Size m_size;
		Optional<Color> m_backGroundColor;
		// TODO orientation
		// TODO renderorder

		TiledProperties m_props;

		TiledSets m_tileSets;
		std::unordered_map<String, TiledLayer> m_layers;

	public:
		CTiledReader() = default;

		CTiledReader(const FilePath& path, TiledFileType fileType)
		{
			this->open(path, fileType);
		}

		CTiledReader(const std::shared_ptr<IReader>& reader, const s3d::FilePath& parentPath, TiledFileType fileType)
		{
			this->open(reader, parentPath, fileType);
		}

		bool open(const FilePath& path, TiledFileType fileType)
		{
			FilePath parentPath = FileSystem::ParentPath(path);

			if (fileType == TiledFileType::Tmx || FileSystem::Extension(path) == L"tmx") {
				XMLReader xml(path, XMLDocumentType::File);
				if (!xml) {
					return false;
				}
				return this->loadXML(xml, parentPath);
			}
			else if (fileType == TiledFileType::Json || FileSystem::Extension(path) == L"json") {
				JSONReader json(path);
				if (!json) {
					return false;
				}
				return this->loadJSON(json, parentPath);
			}
			return false;
		}

		bool open(const std::shared_ptr<IReader>& reader, const s3d::FilePath& parentPath, TiledFileType fileType)
		{
			if (fileType == TiledFileType::Tmx || fileType == TiledFileType::Unspecified) {
				XMLReader xml(reader);
				if (!xml) {
					return false;
				}
				return this->loadXML(xml, parentPath);
			}
			else if (fileType == TiledFileType::Json) {
				JSONReader json(reader);
				if (!json) {
					return false;
				}
				return this->loadJSON(json, parentPath);
			}
			return false;
		}

		Optional<TiledLayer> getLayer(const s3d::String& name) const
		{
			if (m_layers.find(name) == m_layers.end()) {
				return s3d::none;
			}
			return m_layers.at(name);
		}
		bool drawLayer(const s3d::String& name, const s3d::Rect& rect) const
		{
			auto&& layer = this->getLayer(name);
			if (!layer) {

				return false;
			}
			return layer->draw(m_tileSets, rect);
		}
	};

	TiledReader::TiledReader():
		pImpl(std::make_shared<CTiledReader>())
	{
	}

	TiledReader::TiledReader(const FilePath & path, TiledFileType fileType) :
		pImpl(std::make_shared<CTiledReader>(path, fileType))
	{

	}

	TiledReader::TiledReader(const std::shared_ptr<s3d::IReader>& reader, const s3d::FilePath& parentPath,TiledFileType fileType):
		pImpl(std::make_shared<CTiledReader>(reader, parentPath, fileType))
	{
	}

	bool TiledReader::open(const FilePath& path, TiledFileType fileType)
	{
		return pImpl->open(path, fileType);
	}

	bool TiledReader::open(const std::shared_ptr<s3d::IReader>& reader, const s3d::FilePath& parentPath, TiledFileType fileType)
	{
		return pImpl->open(reader, parentPath, fileType);
	}

	Optional<TiledLayer> TiledReader::getLayer(const s3d::String& name) const
	{
		return pImpl->getLayer(name);
	}
	bool TiledReader::drawLayer(const s3d::String& name, const s3d::Rect& rect) const
	{
		return pImpl->drawLayer(name, rect);
	}
}
