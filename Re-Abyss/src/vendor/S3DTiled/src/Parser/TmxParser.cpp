#pragma once
#include "TiledParser.hpp"
#include "../ITileSet.hpp"

#include "../../include/S3DTiled/TiledMap.hpp"
#include "../../include/S3DTiled/TiledLayer.hpp"

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
		bool noneAlpha = str.length <= 7;
		if (noneAlpha) {
			return Color(str);
		}
		String code = L"#" + str.substr(3, 6);
		Color ret(code);
		ret.setAlpha(Parse<uint32>(L"0x" + str.substr(1, 2)));
		return ret;
	}

	class TmxParser
	{
		FilePath m_parentPath;

	public:
		TmxParser() = default;

		bool parse(const s3d::FilePath& path, TiledMap& map)
		{

			XMLReader xml(path, XMLDocumentType::File);
			if (!xml) {
				return false;
			}
			this->m_parentPath = FileSystem::ParentPath(path);

			auto root = xml.root();

			// mapê›íË
			Size mapSize{
				Parse<int32>(root.attribute(L"width").value_or(L"0")),
				Parse<int32>(root.attribute(L"height").value_or(L"0"))
			};
			Size tileSize{
				Parse<int32>(root.attribute(L"tilewidth").value_or(L"0")),
				Parse<int32>(root.attribute(L"tileheight").value_or(L"0"))
			};
			map.init(mapSize, tileSize);

			if (auto && col = root.attribute(L"backgroundcolor")) {
				map.setBackGroundColor(ParseTiledColor(root.attribute(L"backgroundcolor").value()));
			}

			for (auto elm = root.firstChild(); elm; elm = elm.nextSibling()) {
				if (auto && layer = this->tryParseLayer(elm)) {
					map.addLayer(TiledLayer(layer));
				}
				else if (auto && tileSet = this->tryTileSet(elm)) {
					map.addTileSet(std::move(tileSet));
				}
				else if (elm.name() == L"properties") {
					map.setProps(this->parseProps(elm));
				}

			}

			return true;
		}
	private:
		std::shared_ptr<ILayer> tryParseLayer(XMLElement xml)
		{
			if (xml.name() == L"imagelayer") {
				return this->parseImageLayer(xml);
			}
			else if (xml.name() == L"layer") {
				return this->parseTileLayer(xml);

			}
			else if (xml.name() == L"objectgroup") {
				return this->parseObjectGroup(xml);
			}
			return nullptr;
		}

		void parseLayerCommon(ILayer* layer, XMLElement xml)
		{
			// common
			layer->setName(xml.attribute(L"name").value_or(L""));
			layer->setVisible(Parse<bool>(xml.attribute(L"visible").value_or(L"true")));
			layer->setOffset({
				Parse<double>(xml.attribute(L"offsetx").value_or(L"0.0")),
				Parse<double>(xml.attribute(L"offsety").value_or(L"0.0"))
				});

			// ÉvÉçÉpÉeÉBÇÕäKëwÇ™â∫Ç™ÇÈÇÃÇ≈Ç±Ç±Ç≈ÇÕéÊìæÇµÇ»Ç¢
		}
		std::shared_ptr<ILayer> parseImageLayer(XMLElement xml)
		{
			auto layer = std::make_shared<ImageLayer>();
			this->parseLayerCommon(layer.get(), xml);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"image") {
					layer->setTexture(Texture(this->m_parentPath + elm.attribute(L"source").value_or(L"")));
				}
				else if (elm.name() == L"properties") {
					layer->setProps(this->parseProps(elm));
				}
			}
			return layer;
		}

		std::shared_ptr<ILayer> parseObjectGroup(XMLElement xml)
		{
			auto layer = std::make_shared<ObjectGroup>();
			this->parseLayerCommon(layer.get(), xml);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"object") {
					layer->addObject(this->parseObject(elm));
				}
				else if (elm.name() == L"properties") {
					layer->setProps(this->parseProps(elm));
				}
			}
			return layer;
		}


		std::shared_ptr<ILayer> parseTileLayer(XMLElement xml)
		{
			auto layer = std::make_shared<TileLayer>();
			this->parseLayerCommon(layer.get(), xml);

			Grid<GId> grid(
				Parse<uint32>(xml.attribute(L"width").value_or(L"0")),
				Parse<uint32>(xml.attribute(L"height").value_or(L"0"))
			);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"data") {
					int y = 0;
					int x = 0;
					for (auto&& row : elm.text().split(L'\n'))
					{
						for (auto&& col : row.split(L',')) {
							if (col.isEmpty) {
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
				else if (elm.name() == L"properties") {
					layer->setProps(this->parseProps(elm));
				}
			}
			return layer;
		}

		TiledProperties parseProps(XMLElement xml)
		{
			TiledProperties ret;

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"property") {
					ret[elm.attribute(L"name").value_or(L"")] = this->parseProp(elm);
				}
			}
			return ret;
		}

		TiledProperty parseProp(XMLElement xml)
		{
			const String& type = xml.attribute(L"type").value_or(L"string");
			const String& value = xml.attribute(L"value").value_or(L"");

			if (type == L"bool") {
				return Parse<bool>(value);
			}
			else if (type == L"color") {
				return ParseTiledColor(value);
			}
			else if (type == L"float") {
				return Parse<double>(value);
			}
			else if (type == L"int") {
				return Parse<int32>(value);
			}
			else {
				return type == L"file" ? this->m_parentPath + value : value;
			}
		}
		bool tryParseShape(XMLElement elm, Shape & shape, const Vec2 & size)
		{
			if (elm.name() == L"ellipse") {
				shape = Ellipse({ 0,0 }, size);
				return true;
			}
			if (elm.name() == L"polygon") {
				Array<Vec2> pos;
				for (auto&& row : elm.attribute(L"points")->split(L' '))
				{
					const auto& s = row.split(L',');
					pos.emplace_back(
						Parse<double>(s[0]),
						Parse<double>(s[1])
					);
				}
				shape = Polygon(pos);
				return true;
			}
			if (elm.name() == L"polyline") {
				Array<Vec2> pos;
				for (auto&& row : elm.attribute(L"points")->split(L' '))
				{
					const auto& s = row.split(L',');
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


		TiledObject parseObject(XMLElement xml)
		{
			TiledObject obj;
			obj.id = Parse<uint32>(xml.attribute(L"id").value_or(L"0"));
			obj.name = xml.attribute(L"name").value_or(L"");
			obj.type = xml.attribute(L"type").value_or(L"");
			obj.pos = {
				Parse<double>(xml.attribute(L"x").value_or(L"0")),
				Parse<double>(xml.attribute(L"y").value_or(L"0"))
			};
			obj.rotation = Parse<double>(xml.attribute(L"rotation").value_or(L"0"));
			if (auto && gId = xml.attribute(L"gid")) {
				// TODO flip
				obj.gId = Parse<GId>(xml.attribute(L"gid").value());
			}
			Vec2 size{
				Parse<double>(xml.attribute(L"width").value_or(L"0")),
				Parse<double>(xml.attribute(L"height").value_or(L"0"))
			};
			//shape
			bool isRect = true;
			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (this->tryParseShape(elm, obj.shape, size))
				{
					isRect = false;
				}
				else if (elm.name() == L"properties") {
					obj.setProps(this->parseProps(elm));
				}
			}
			if (isRect) {
				obj.shape = RectF({ 0,0 }, size);
			}
			return obj;
		}

		TiledAnimation parseAnimation(XMLElement xml)
		{
			TiledAnimation ret;

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() != L"frame") {
					continue;
				}
				int32 duration = Parse<int32>(elm.attribute(L"duration").value_or(L"0"));
				TileId tileId = Parse<TileId>(elm.attribute(L"tileid").value_or(L"0"));
				ret.addFrame(tileId, duration);
			}
			return ret;
		}

		std::unique_ptr<ITileSet> tryTileSet(XMLElement xml)
		{
			if (xml.name() != L"tileset") {
				return nullptr;
			}
			if (xml.attribute(L"columns").value_or(L"0") == L"0") {
				return this->parseVariousTileSet(xml);
			}
			else {
				return this->parseUniformTileSet(xml);
			}
		}

		void parseTileSetCommon(ITileSet * tileSet, XMLElement xml)
		{
			tileSet->setFirstGId(Parse<GId>(xml.attribute(L"firstgid").value_or(L"0")));
			tileSet->setTileCount(Parse<uint32>(xml.attribute(L"tilecount").value_or(L"0")));
			tileSet->setColumns(Parse<uint32>(xml.attribute(L"columns").value_or(L"0")));

			// animationÇÕäKëwÇ™â∫Ç™ÇÈÇÃÇ≈Ç±Ç±Ç≈ÇÕÇ‚ÇÁÇ»Ç¢
		}

		void tryParseTileInfo(ITileSet * tileSet, TileId tileId, XMLElement xml)
		{
			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"animation") {
					tileSet->addAnimation(tileId, this->parseAnimation(elm));
				}
				else if (elm.name() == L"properties") {
					tileSet->addProps(tileId, this->parseProps(elm));
				}
			}
		}
		std::unique_ptr<ITileSet> parseUniformTileSet(XMLElement xml)
		{
			auto tileSet = std::make_unique<UniformTileSet>();
			this->parseTileSetCommon(tileSet.get(), xml);

			tileSet->setTileSize({
				Parse<int32>(xml.attribute(L"tilewidth").value_or(L"0")),
				Parse<int32>(xml.attribute(L"tileheight").value_or(L"0"))
			});

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"image") {
					tileSet->setTexture(Texture(this->m_parentPath + elm.attribute(L"source").value_or(L"")));
				}else if (elm.name() == L"tile") {
					TileId tileId = Parse<TileId>(elm.attribute(L"id").value_or(L"0"));
					this->tryParseTileInfo(tileSet.get(), tileId, elm);
				}
			}

			return tileSet;
		}

		std::unique_ptr<ITileSet> parseVariousTileSet(XMLElement xml)
		{
			auto tileSet = std::make_unique<VariousTileSet>();
			this->parseTileSetCommon(tileSet.get(), xml);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"tile") {
					TileId tileId = Parse<TileId>(elm.attribute(L"id").value_or(L"0"));
					this->tryParseTileInfo(tileSet.get(), tileId, elm);

					for (auto image = elm.firstChild(); image; image = image.nextSibling()) {
						if (image.name() == L"image") {
							tileSet->addTexture(tileId, Texture(this->m_parentPath + image.attribute(L"source").value_or(L"")));
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
	bool ParseTmx(const s3d::FilePath& path, TiledMap& map)
	{
		TmxParser parser;
		return parser.parse(path, map);
	}
}