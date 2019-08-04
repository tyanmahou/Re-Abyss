#include <S3DTiled/TiledProperty.hpp>

using namespace s3d;

namespace s3dTiled
{
	TiledProperty::TiledProperty() :
		m_type(Type::None)
	{}

	TiledProperty::TiledProperty(const TiledProperty & other)
	{
		*this = other;
	}
	TiledProperty::TiledProperty(TiledProperty && other)
	{
		*this = std::move(other);
	}
	TiledProperty::TiledProperty(bool b):
		m_type(Type::Bool),
		b(b)
	{
	}
	TiledProperty::TiledProperty(const s3d::Color& col):
		m_type(Type::Color),
		col(col)
	{
	}
	TiledProperty::TiledProperty(double f):
		m_type(Type::Float),
		f(f)
	{
	}
	TiledProperty::TiledProperty(s3d::int32 i):
		m_type(Type::Int),
		i(i)
	{
	}
	TiledProperty::TiledProperty(const s3d::String& str):
		m_type(Type::String),
		str(new String(str))
	{
	}
	TiledProperty::~TiledProperty()
	{
		this->clear();
	}
	bool TiledProperty::toBool() const
	{
		return this->b;
	}
	TiledProperty::operator bool() const
	{
		return this->toBool();
	}
	Color TiledProperty::toColor() const
	{
		return this->col;
	}
	TiledProperty::operator s3d::Color() const
	{
		return this->toColor();
	}
	double TiledProperty::toFloat() const
	{
		return this->f;
	}
	TiledProperty::operator double() const
	{
		return this->toFloat();
	}
	int32 TiledProperty::toInt() const
	{
		return this->i;
	}
	TiledProperty::operator s3d::int32() const
	{
		return this->toInt();
	}
	const String& TiledProperty::toString() const
	{
		return *this->str;
	}
	TiledProperty::operator s3d::String() const
	{
		return this->toString();
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
			delete this->str;
			this->str = nullptr;
			break;
		default:
			break;
		}
		this->m_type = Type::None;
	}
	TiledProperty& TiledProperty::operator=(const TiledProperty & other)
	{
		if (this == &other) {
			return *this;
		}
		if (this->m_type != other.m_type) {
			this->clear();
		}

		switch (other.m_type)
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
		this->m_type = other.m_type;
		return *this;
	}
	TiledProperty& TiledProperty::operator=(TiledProperty && other)
	{
		if (this == &other) {
			return *this;
		}
		this->clear();
		switch (other.m_type)
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
			this->str = other.str;
			break;
		default:
			break;
		}
		this->m_type = other.m_type;

		other.m_type = Type::None;

		return *this;
	}
}