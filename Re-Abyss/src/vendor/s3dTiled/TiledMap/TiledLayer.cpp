#include"TiledLayer.hpp"
#include"TiledObject.hpp"
#include"TiledSets.hpp"

#include<Siv3D.hpp>

namespace {
	using namespace s3dTiled;
	using TileMap = Grid<GId>;

	void ParseCommon(XMLElement elm, bool& visible, Vec2& offset)
	{
		visible = Parse<bool>(elm.attribute(L"visible").value_or(L"true"));
		offset = {
			Parse<double>(elm.attribute(L"offsetx").value_or(L"0.0")),
			Parse<double>(elm.attribute(L"offsety").value_or(L"0.0"))
		};
	}

	void ParseData(XMLElement elm, TileMap& map)
	{
		if (elm.name() == L"data") {
			int y = 0;
			int x = 0;
			for (auto&& row : elm.text().split(L'\n'))
			{
				for (auto&& col : row.split(L',')) {
					if (col.isEmpty) {
						continue;
					}
					map[y][x] = Parse<GId>(col);
					x++;
				}
				x = 0;
				y++;
			}
		}
	}
}
namespace s3dTiled
{
	class TiledLayer::ITiledLayer
	{
	protected:
		bool m_visible = true;
		Vec2 m_offset;
		TiledProperties m_props;
	public:
		ITiledLayer() = default;

		virtual ~ITiledLayer() = default;
		virtual bool draw(const TiledSets& tileSets, const Rect& rect) const = 0;
		virtual TiledLayer::Type getType() const = 0;
	};

	/// <summary>
	/// Image Layer
	/// </summary>
	class ImageLayer : public TiledLayer::ITiledLayer
	{
		Texture m_texture;
	public:
		ImageLayer() = default;
		ImageLayer(XMLElement xml, const  FilePath& parentPath)
		{
			::ParseCommon(xml, m_visible, m_offset);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				ParseProps(elm, this->m_props, parentPath);
				if (elm.name() == L"image" && !m_texture) {
					m_texture = Texture(parentPath + elm.attribute(L"source").value_or(L""));
				}
			}
		}
		bool draw(const TiledSets&, const Rect & rect) const override
		{
			if (!m_visible) {
				return false;
			}
			if (!RectF(m_offset, m_texture.size).intersects(rect)) {
				// ”ÍˆÍŠO
				return false;
			}
			m_texture.draw(m_offset);

			return true;
		}
		TiledLayer::Type getType() const override
		{
			return TiledLayer::Type::Image;
		}
	};

	/// <summary>
	/// Tile Layer
	/// </summary>
	class TileLayer : public TiledLayer::ITiledLayer
	{
		TileMap m_gIds;
	public:
		TileLayer() = default;
		TileLayer(XMLElement xml, const  FilePath& parentPath = L"") :
			m_gIds(
				Parse<uint32>(xml.attribute(L"width").value_or(L"0")),
				Parse<uint32>(xml.attribute(L"height").value_or(L"0"))
			)
		{
			::ParseCommon(xml, m_visible, m_offset);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				ParseProps(elm, this->m_props, parentPath);
				::ParseData(elm, m_gIds);
			}
		}

		bool draw(const TiledSets& tileSets, const Rect& rect) const override
		{
			if (!m_visible) {
				return false;
			}

			Vec2 tileSize = tileSets.getTileSize();

			GId xStart = static_cast<GId>(rect.x / tileSize.x);
			GId yStart = static_cast<GId>(rect.y / tileSize.y);

			GId xEnd = xStart + static_cast<GId>(rect.w / tileSize.x);
			GId yEnd = yStart + static_cast<GId>(rect.h / tileSize.y);


			for (GId y = yStart; y < yEnd; ++y) {
				for (GId x = xStart; x < xEnd; ++x) {
					GId gId = m_gIds[y][x];
					if (gId == 0) {
						continue;
					}
					auto&& texture = tileSets.getTile(gId);
					Vec2 pos = { x * tileSize.x, y *  tileSize.y };
					if (tileSets.needAxisAdjust(gId)) {
						// axis‚Ì’²®
						pos.y -= (texture.size.y - tileSize.y);
					}
					texture.draw(pos);
				}
			}
			return true;
		}
		TiledLayer::Type getType() const override
		{
			return TiledLayer::Type::Tile;
		}
	};

	/// <summary>
	/// Object Layer
	/// </summary>
	class ObjectLayer : public TiledLayer::ITiledLayer
	{
		Array<TiledObject> m_objects;

	public:
		ObjectLayer() = default;
		ObjectLayer(XMLElement xml, const  FilePath& parentPath = L"")
		{
			::ParseCommon(xml, m_visible, m_offset);

			for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
				ParseProps(elm, this->m_props, parentPath);
				if (elm.name() == L"object") {
					m_objects.emplace_back(elm, parentPath);
				}
			}
		}

		bool draw(const TiledSets& /*tileSets*/, const Rect& /*rect*/) const override
		{
			if (!m_visible) {
				return false;
			}
			// TODO
			return true;
		}
		TiledLayer::Type getType() const override
		{
			return TiledLayer::Type::Object;
		}
	};

	TiledLayer::TiledLayer(s3d::XMLElement xml, const s3d::FilePath& parentPath)
	{
		// TODO make_shared
		if (xml.name() == L"imagelayer") {
			this->pImpl = std::make_shared<ImageLayer>(xml, parentPath);
		}else if (xml.name() == L"layer") {
			this->pImpl = std::make_shared<TileLayer>(xml, parentPath);
		}else if (xml.name() == L"objectgroup") {
			this->pImpl = std::make_shared<ObjectLayer>(xml, parentPath);
		}
	}
	bool TiledLayer::draw(const TiledSets& tileSets, const s3d::Rect& rect) const
	{
		return pImpl->draw(tileSets, rect);
	}
	TiledLayer::Type TiledLayer::getType() const
	{
		if (!this->pImpl) {
			return Type::None;
		}
		return this->pImpl->getType();
	}
}