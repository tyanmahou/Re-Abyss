#pragma once

#include <variant>
#include <type_traits>

namespace abyss::Decor
{
	class DecorType
	{
	public:
		enum class General
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

	public:
		DecorType():
			m_value(General::None)
		{}

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

		s3d::uint32 categoryId() const
		{
			return static_cast<s3d::uint32>(m_value.index());
		}
	private:
		std::variant<General, City, Gimmick> m_value;
	};
}