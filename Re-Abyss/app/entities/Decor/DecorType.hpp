#pragma once

#include <variant>
#include <type_traits>

namespace abyss::decor
{
	class DecorType
	{
	public:
		enum class Common
		{
			Common,
		};

		enum class City
		{
			StreetLight,
		};

		enum class Gimmick
		{
			Door,
		};

		enum class Map
		{
			Common,
		};

	public:
		DecorType() = default;

		DecorType(const Common& value):
			m_value(value)
		{}

		DecorType(const City& value) :
			m_value(value)
		{}

		DecorType(const Gimmick& value) :
			m_value(value)
		{}

		DecorType(const Map& value) :
			m_value(value)
		{}

		DecorType& operator =(const Common& value)
		{
			this->m_value = value;
			return *this;
		}

		DecorType& operator =(const City& value)
		{
			this->m_value = value;
			return *this;
		}

		DecorType& operator =(const Gimmick& value)
		{
			this->m_value = value;
			return *this;
		}

		DecorType& operator =(const Map& value)
		{
			this->m_value = value;
			return *this;
		}
	private:
		std::variant<Common, City, Gimmick, Map> m_value;
	};
}