#include "TiledParser.hpp"
#include "../TiledSets/TileSetBase.hpp"
#include "../TiledMap/CTiledMap.hpp"

#include <S3DTiled/TiledLayer.hpp>

#include <Siv3D/Types.hpp>
#include <Siv3D/Color.hpp>
#include <Siv3D/XMLReader.hpp>
#include <Siv3D/Parse.hpp>
#include <Siv3D/FileSystem.hpp>

using namespace s3d;

namespace
{
	using namespace s3dTiled;

	s3d::Color ParseTiledColor(const s3d::String& str)
	{
		bool noneAlpha = str.length() <= 7;
		if (noneAlpha) {
			return Color(str);
		}
		String code = U"#" + str.substr(3, 6);
		Color ret(code);
		ret.setA(Parse<uint32>(U"0x" + str.substr(1, 2)));
		return ret;
	}

	class TmxParser
	{
		FilePath m_parentPath;

	public:
		TmxParser() = default;

		std::shared_ptr<CTiledMap> parse(const s3d::FilePath& path)
		{
			XMLReader root(path);
			if (!root) {
				return nullptr;
			}
			this->m_parentPath = FileSystem::ParentPath(path);

			// mapê›íË
			Size mapSize{
				Parse<int32>(root.attribute(U"width").value_or(U"0")),
				Parse<int32>(root.attribute(U"height").value_or(U"0"))
			};
			Size tileSize{
				Parse<int32>(root.attribute(U"tilewidth").value_or(U"0")),
				Parse<int32>(root.attribute(U"tileheight").value_or(U"0"))
			};
			auto map = std::make_shared<CTiledMap>(mapSize, tileSize);

			if (auto && col = root.attribute(U"backgroundcolor")) {
				map->setBackGroundColor(ParseTiledColor(root.attribute(U"backgroundcolor").value()));
			}

			for (auto elm = root.firstChild(); elm; elm = elm.nextSibling()) {
				if (auto && layer = this->tryParseLayer(elm)) {
					map->addLayer(TiledLayer(layer));
				}
				else if (auto && tileSet = this->tryTileSet(elm)) {
					map->addTileSet(std::move(tileSet));
				}
				else if (elm.name() == U"properties") {
					map->setProps(this->parseProps(elm));
				}

			}

			return map;
		}
	private:
		std::shared_ptr<TiledLayerBase> tryParseLayer(const XMLElement& xml)
		{
			if (xml.name() == U"imagelayer") {
				return this->parseImageLayer(xml);
			}
			else if (xml.name() == U"layer") {
				return this->parseTileLayer(xml);

			}
			else if (xml.name() == U"objectgroup") {
				return this->parseObjectGroup(xml);
			}
			else if (xml.name() == U"group") {
				return this->parseGroupLayer(xml);
			}
			return nullptr;
		}

		void parseLayerCommon(TiledLayerBase* layer, const XMLElement& xml)
		{
			// common
			layer->setName(xml.attribute(U"name").value_or(U""));
			layer->setVisible(Parse<bool>(xml.attribute(U"visible").value_or(U"true")));
			layer->setOffset({
				Parse<double>(xml.attribute(U"offsetx").value_or(U"0.0")),
				Parse<double>(xml.attribute(U"offsety").value_or(U"0.0"))
				});

			// ÉvÉçÉpÉeÉBÇÕäKëwÇ™â∫Ç™ÇÈÇÃÇ≈Ç±Ç±Ç≈ÇÕéÊìæÇµÇ»Ç¢
		}
		std::shared_ptr<TiledLayerBase> parseImageLayer(const XMLElement& xml)
		{
			auto layer = std::make_shared<ImageLayer>();
			this->parseLayerCommon(layer.get(), xml);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == U"image") {
					layer->setTexture(Texture(this->m_parentPath + elm.attribute(U"source").value_or(U"")));
				}
				else if (elm.name() == U"properties") {
					layer->setProps(this->parseProps(elm));
				}
			}
			return layer;
		}

		std::shared_ptr<TiledLayerBase> parseObjectGroup(const XMLElement& xml)
		{
			auto layer = std::make_shared<ObjectGroup>();
			this->parseLayerCommon(layer.get(), xml);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == U"object") {
					layer->addObject(this->parseObject(elm));
				}
				else if (elm.name() == U"properties") {
					layer->setProps(this->parseProps(elm));
				}
			}
			return layer;
		}


		std::shared_ptr<TiledLayerBase> parseTileLayer(const XMLElement& xml)
		{
			auto layer = std::make_shared<TileLayer>();
			this->parseLayerCommon(layer.get(), xml);

			Grid<GId> grid(
				Parse<uint32>(xml.attribute(U"width").value_or(U"0")),
				Parse<uint32>(xml.attribute(U"height").value_or(U"0"))
			);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == U"data") {
					int y = 0;
					int x = 0;
					for (auto&& row : elm.text().split(U'\n'))
					{
						for (auto&& col : row.split(U',')) {
							if (col.isEmpty()) {
								continue;
							}
							grid[y][x] = Parse<GId>(col);
							x++;
						}
						x = 0;
						y++;
					}
					layer->setGrid(std::move(grid));
				}
				else if (elm.name() == U"properties") {
					layer->setProps(this->parseProps(elm));
				}
			}
			return layer;
		}

		std::shared_ptr<TiledLayerBase> parseGroupLayer(const XMLElement& xml)
		{
			auto layer = std::make_shared<GroupLayer>();
			this->parseLayerCommon(layer.get(), xml);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (auto&& child = this->tryParseLayer(elm)) {
					layer->addLayer(TiledLayer(child));
				}
				else if (elm.name() == U"properties") {
					layer->setProps(this->parseProps(elm));
				}
			}
			return layer;
		}

		TiledProperties parseProps(const XMLElement& xml)
		{
			TiledProperties ret;

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == U"property") {
					ret[elm.attribute(U"name").value_or(U"")] = this->parseProp(elm);
				}
			}
			return ret;
		}

		TiledProperty parseProp(const XMLElement& xml)
		{
			const String& type = xml.attribute(U"type").value_or(U"string");
			const String& value = xml.attribute(U"value").value_or(U"");

			if (type == U"bool") {
				return Parse<bool>(value);
			}
			else if (type == U"color") {
				return ParseTiledColor(value);
			}
			else if (type == U"float") {
				return Parse<double>(value);
			}
			else if (type == U"int") {
				return Parse<int32>(value);
			}
			else {
				return type == U"file" ? this->m_parentPath + value : value;
			}
		}
		bool tryParseShape(const XMLElement& elm, TiledShape & shape, const Vec2 & size)
		{
			if (elm.name() == U"ellipse") {
				shape = Ellipse({ 0,0 }, size);
				return true;
			}
			if (elm.name() == U"polygon") {
				Array<Vec2> pos;
				for (auto&& row : elm.attribute(U"points")->split(L' '))
				{
					const auto& s = row.split(U',');
					pos.emplace_back(
						Parse<double>(s[0]),
						Parse<double>(s[1])
					);
				}
				shape = Polygon(pos);
				return true;
			}
			if (elm.name() == U"polyline") {
				Array<Vec2> pos;
				for (auto&& row : elm.attribute(U"points")->split(U' '))
				{
					const auto& s = row.split(U',');
					pos.emplace_back(
						Parse<double>(s[0]),
						Parse<double>(s[1])
					);
				}
				shape = LineString(pos);
				return true;
			}
			return false;
		}


		TiledObject parseObject(const XMLElement& xml)
		{
			TiledObject obj;
			obj.id = Parse<uint32>(xml.attribute(U"id").value_or(U"0"));
			obj.name = xml.attribute(U"name").value_or(U"");
			obj.type = xml.attribute(U"type").value_or(U"");
			obj.pos = {
				Parse<double>(xml.attribute(U"x").value_or(U"0")),
				Parse<double>(xml.attribute(U"y").value_or(U"0"))
			};
			obj.rotation = Parse<double>(xml.attribute(U"rotation").value_or(U"0"));
			if (auto && gId = xml.attribute(U"gid")) {
				// TODO flip
				obj.gId = Parse<GId>(xml.attribute(U"gid").value());
			}
			Vec2 size{
				Parse<double>(xml.attribute(U"width").value_or(U"0")),
				Parse<double>(xml.attribute(U"height").value_or(U"0"))
			};
			//shape
			bool isRect = true;
			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (this->tryParseShape(elm, obj.shape, size))
				{
					isRect = false;
				}
				else if (elm.name() == U"properties") {
					obj.setProps(this->parseProps(elm));
				}
			}
			if (isRect) {
				obj.shape = RectF({ 0,0 }, size);
			}
			return obj;
		}

		TiledAnimation parseAnimation(const XMLElement& xml)
		{
			TiledAnimation ret;

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() != U"frame") {
					continue;
				}
				int32 duration = Parse<int32>(elm.attribute(U"duration").value_or(U"0"));
				TileId tileId = Parse<TileId>(elm.attribute(U"tileid").value_or(U"0"));
				ret.addFrame(tileId, duration);
			}
			return ret;
		}

		std::unique_ptr<TileSetBase> tryTileSet(const XMLElement& xml)
		{
			if (xml.name() != U"tileset") {
				return nullptr;
			}
			if (xml.attribute(U"columns").value_or(U"0") == U"0") {
				return this->parseVariousTileSet(xml);
			}
			else {
				return this->parseUniformTileSet(xml);
			}
		}

		void parseTileSetCommon(TileSetBase* tileSet, const XMLElement& xml)
		{
			tileSet->setFirstGId(Parse<GId>(xml.attribute(U"firstgid").value_or(U"0")));
			tileSet->setTileCount(Parse<uint32>(xml.attribute(U"tilecount").value_or(U"0")));
			tileSet->setColumns(Parse<uint32>(xml.attribute(U"columns").value_or(U"0")));

			// animationÇÕäKëwÇ™â∫Ç™ÇÈÇÃÇ≈Ç±Ç±Ç≈ÇÕÇ‚ÇÁÇ»Ç¢
		}

		void tryParseTileInfo(TileSetBase* tileSet, TileId tileId, const XMLElement& xml)
		{
			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == U"animation") {
					tileSet->addAnimation(tileId, this->parseAnimation(elm));
				}
				else if (elm.name() == U"properties") {
					tileSet->addProps(tileId, this->parseProps(elm));
				}
			}
		}
		std::unique_ptr<TileSetBase> parseUniformTileSet(const XMLElement& xml)
		{
			auto tileSet = std::make_unique<UniformTileSet>();
			this->parseTileSetCommon(tileSet.get(), xml);

			tileSet->setTileSize({
				Parse<int32>(xml.attribute(U"tilewidth").value_or(U"0")),
				Parse<int32>(xml.attribute(U"tileheight").value_or(U"0"))
			});

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == U"image") {
					tileSet->setTexture(Texture(this->m_parentPath + elm.attribute(U"source").value_or(U"")));
				}else if (elm.name() == U"tile") {
					TileId tileId = Parse<TileId>(elm.attribute(U"id").value_or(U"0"));
					this->tryParseTileInfo(tileSet.get(), tileId, elm);
				}
			}

			return tileSet;
		}

		std::unique_ptr<TileSetBase> parseVariousTileSet(const XMLElement& xml)
		{
			auto tileSet = std::make_unique<VariousTileSet>();
			this->parseTileSetCommon(tileSet.get(), xml);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == U"tile") {
					TileId tileId = Parse<TileId>(elm.attribute(U"id").value_or(U"0"));
					this->tryParseTileInfo(tileSet.get(), tileId, elm);

					for (auto image = elm.firstChild(); image; image = image.nextSibling()) {
						if (image.name() == U"image") {
							tileSet->addTexture(tileId, Texture(this->m_parentPath + image.attribute(U"source").value_or(U"")));
							break;
						}
					}
				}
			}
			return tileSet;
		}
	};


}
namespace s3dTiled
{
	std::shared_ptr<CTiledMap> ParseTmx(const s3d::FilePath& path)
	{
		TmxParser parser;
		return parser.parse(path);
	}
}