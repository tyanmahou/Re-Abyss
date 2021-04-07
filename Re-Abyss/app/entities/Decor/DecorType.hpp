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

		template<class Type>
		DecorType(const Type& value):
			m_value(value)
		{}
		template<class Type>
		DecorType& operator =(const Type& value)
		{
			this->m_value = value;
			return *this;
		}
	private:
		std::variant<Common, City, Gimmick, Map> m_value;
	};
}