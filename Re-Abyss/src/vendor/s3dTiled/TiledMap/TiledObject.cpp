#include "TiledObject.hpp"

#include<Siv3D/XMLReader.hpp>
#include<Siv3D/Parse.hpp>

using namespace s3d;

namespace {

	bool ParseShape(XMLElement elm, Shape& shape, const Vec2& size)
	{
		if (elm.name() == L"ellipse") {
			shape = Ellipse({ 0,0 }, size);
			return false;
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
			return false;
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
			return false;
		}
		return true;
	}
}

namespace s3dTiled
{

	TiledObject::TiledObject(XMLElement xml, const FilePath& parentPath) :
		m_id(Parse<uint32>(xml.attribute(L"id").value_or(L"0"))),
		m_name(xml.attribute(L"name").value_or(L"")),
		m_type(xml.attribute(L"type").value_or(L"")),
		m_pos(
			Parse<double>(xml.attribute(L"x").value_or(L"0")),
			Parse<double>(xml.attribute(L"y").value_or(L"0"))
		),
		m_rotation(Parse<double>(xml.attribute(L"rotation").value_or(L"0")))
	{
		if (auto && gId = xml.attribute(L"gid")) {
			// TODO flip
			this->m_gId = Parse<GId>(xml.attribute(L"gid").value());
		}

		Vec2 size{
			Parse<double>(xml.attribute(L"width").value_or(L"0")),
			Parse<double>(xml.attribute(L"height").value_or(L"0"))
		};
		bool isRect = true;
		for (auto elm = xml.firstChild(); elm; elm = elm.nextSibling()) {
			ParseProps(elm, this->m_props, parentPath);
			isRect &= ::ParseShape(elm, m_shape, size);
		}
		if (isRect) {
			m_shape = RectF({ 0,0 }, size);
		}
	}
}