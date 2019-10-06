#include <S3DTiled/TiledProperty.hpp>

using namespace s3d;

namespace s3dTiled
{
	TiledProperty::TiledProperty() :
		m_type(Type::None)
	{
		memset(&m_storage, 0, sizeof(m_storage));
	}

	TiledProperty::TiledProperty(const TiledProperty & other) :
		m_type(Type::None)
	{
		*this = other;
	}
	TiledProperty::TiledProperty(TiledProperty && other)noexcept :
		m_type(Type::None)
	{
		*this = std::move(other);
	}
	TiledProperty::TiledProperty(bool b):
		m_type(Type::Bool)
	{
		m_storage.b = b;
	}
	TiledProperty::TiledProperty(const s3d::Color& col):
		m_type(Type::Color)
	{
		m_storage.col = col;
	}
	TiledProperty::TiledProperty(double f):
		m_type(Type::Float)
	{
		m_storage.f = f;
	}
	TiledProperty::TiledProperty(s3d::int32 i):
		m_type(Type::Int)
	{
		m_storage.i = i;
	}
	TiledProperty::TiledProperty(const s3d::String& str):
		m_type(Type::String)
	{
		m_storage.str = new String(str);
	}
	TiledProperty::~TiledProperty()
	{
		this->clear();
	}
	bool TiledProperty::toBool() const
	{
		return this->m_storage.b;
	}
	TiledProperty::operator bool() const
	{
		return this->toBool();
	}
	Color TiledProperty::toColor() const
	{
		return this->m_storage.col;
	}
	TiledProperty::operator s3d::Color() const
	{
		return this->toColor();
	}
	double TiledProperty::toFloat() const
	{
		return this->m_storage.f;
	}
	TiledProperty::operator double() const
	{
		return this->toFloat();
	}
	int32 TiledProperty::toInt() const
	{
		return this->m_storage.i;
	}
	TiledProperty::operator s3d::int32() const
	{
		return this->toInt();
	}
	const String& TiledProperty::toString() const
	{
		return *this->m_storage.str;
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
			this->m_storage.b = false;
			break;
		case Type::Color:
			this->m_storage.col = Color();
			break;
		case Type::Float:
			this->m_storage.f = 0.0;
			break;
		case Type::Int:
			this->m_storage.i = 0;
			break;
		case Type::String:
			delete this->m_storage.str;
			this->m_storage.str = nullptr;
			break;
		default:
			break;
		}
		this->m_type = Type::None;
	}
	void TiledProperty::reset(Type type)
	{
		if (m_type == type) {
			return;
		}
		this->clear();
		switch (type)
		{
		case s3dTiled::TiledProperty::Type::String:
			m_storage.str = new String();
			break;
		default:
			break;
		}
		m_type = type;
	}
	TiledProperty& TiledProperty::operator=(const TiledProperty & other)
	{
		if (this == &other) {
			return *this;
		}
		this->reset(other.m_type);

		switch (other.m_type)
		{
		case Type::Bool:
			this->m_storage.b = other.m_storage.b;
			break;
		case Type::Color:
			this->m_storage.col = other.m_storage.col;
			break;
		case Type::Float:
			this->m_storage.f = other.m_storage.f;
			break;
		case Type::Int:
			this->m_storage.i = other.m_storage.i;
			break;
		case Type::String:
			if (this->m_storage.str == nullptr) {
				this->m_storage.str = new String();
			}
			*this->m_storage.str = *other.m_storage.str;
			break;
		default:
			break;
		}
		return *this;
	}
	TiledProperty& TiledProperty::operator=(TiledProperty && other) noexcept
	{
		if (this == &other) {
			return *this;
		}
		this->clear();
		switch (other.m_type)
		{
		case Type::Bool:
			this->m_storage.b = other.m_storage.b;
			break;
		case Type::Color:
			this->m_storage.col = other.m_storage.col;
			break;
		case Type::Float:
			this->m_storage.f = other.m_storage.f;
			break;
		case Type::Int:
			this->m_storage.i = other.m_storage.i;
			break;
		case Type::String:
			this->m_storage.str = other.m_storage.str;
			break;
		default:
			break;
		}
		this->m_type = other.m_type;
		other.m_type = Type::None;
		memset(&other.m_storage, 0, sizeof(other.m_storage));

		return *this;
	}
}