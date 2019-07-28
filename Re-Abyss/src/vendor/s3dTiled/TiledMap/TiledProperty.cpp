#include"TiledProperty.hpp"

#include"TiledUtil.hpp"

#include<Siv3D/Parse.hpp>
#include<Siv3D/XMLReader.hpp>

using namespace s3d;

namespace s3dTiled
{
	TiledProperty::TiledProperty():
		m_type(Type::None)
	{}

	TiledProperty::TiledProperty(XMLElement xml, const FilePath& parentPath)
	{
		const String& type = xml.attribute(L"type").value_or(L"string");
		const String& value = xml.attribute(L"value").value_or(L"");

		if (type == L"bool") {
			this->b = Parse<bool>(value);
			this->m_type = Type::Bool;
		}
		else if (type == L"color") {
			this->col = ParseTiledColor(value);
			this->m_type = Type::Color;
		}
		else if (type == L"float") {
			this->f = Parse<float>(value);
			this->m_type = Type::Float;
		}
		else if (type == L"int") {
			this->i = Parse<int32>(value);
			this->m_type = Type::Int;
		}
		else {
			this->str = new String(type == L"file" ? value + parentPath : value);
			this->m_type = Type::String;
		}
	}
	TiledProperty::TiledProperty(const TiledProperty& other)
	{
		*this = other;
	}
	TiledProperty::~TiledProperty()
	{
		this->clear();
	}
	bool TiledProperty::toBool() const
	{
		return this->b;
	}
	Color TiledProperty::toColor() const
	{
		return this->col;
	}
	float TiledProperty::toFloat() const
	{
		return this->f;
	}
	int32 TiledProperty::toInt() const
	{
		return this->i;
	}
	const String& TiledProperty::toString() const
	{
		return *this->str;
	}
	TiledProperty::Type TiledProperty::getType() const
	{
		return m_type;
	}
	void TiledProperty::clear()
	{
		switch (this->m_type)
		{
		case Type::Bool:
			this->b = false;
			break;
		case Type::Color:
			this->col = Color();
			break;
		case Type::Float:
			this->f = 0.0;
			break;
		case Type::Int:
			this->i = 0;
			break;
		case Type::String:
			if (this->str != nullptr) {
				delete this->str;
			}
			break;
		default:
			break;
		}
		this->m_type = Type::None;
	}
	TiledProperty& TiledProperty::operator=(const TiledProperty& other)
	{
		if (this == &other) {
			return *this;
		}
		if (this->m_type != other.m_type) {
			this->clear();
		}

		switch (this->m_type)
		{
		case Type::Bool:
			this->b = other.b;
			break;
		case Type::Color:
			this->col = other.col;
			break;
		case Type::Float:
			this->f = other.f;
			break;
		case Type::Int:
			this->i = other.i;
			break;
		case Type::String:
			if (this->str == nullptr) {
				this->str = new String();
			}
			*this->str = *other.str;
			break;
		default:
			break;
		}
		return *this;
	}
	void ParseProps(XMLElement map, TiledProperties& props, const FilePath& parentPath)
	{
		if (map.name() == L"properties") {
			for (auto elm = map.firstChild(); elm; elm = elm.nextSibling()) {
				if (elm.name() == L"property") {
					props[elm.attribute(L"name").value_or(L"")] = TiledProperty(
						elm,
						parentPath
					);
				}
			}
		}
	}
}