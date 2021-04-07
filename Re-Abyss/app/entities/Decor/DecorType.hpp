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
			None,
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
		DecorType& operator =(const Common& value)
		{
			this->m_value = value;
			return *this;
		}

		template<class Type>
		bool operator ==(const Type& value) const
		{
			return std::visit([value]<class U>(const U& v) {
				if constexpr (!std::is_same_v<Type, U>) {
					return false;
				} else {
					return v == value;
				}
			}, m_value);
		}

		template<class Type>
		bool operator !=(const Type& value) const
		{
			return !(*this == value);
		}

		template<class Func>
		decltype(auto) visit(const Func& visitor) const
		{
			return std::visit(visitor, m_value);
		}
	private:
		std::variant<Common, City, Gimmick, Map> m_value;
	};
}