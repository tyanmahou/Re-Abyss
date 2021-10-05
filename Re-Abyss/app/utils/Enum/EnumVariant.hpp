#pragma once
#include "EnumTraits.hpp"
#include <variant>
#include <abyss/utils/Meta/IndexSeqVisit.hpp>

namespace Enum
{
	//-----------------------------------
	// Concept

	template<class T>
	struct IsEnumVariant : std::false_type {};
	template<EnumType... E> requires (sizeof...(E) > 0)
	struct IsEnumVariant<std::variant<E...>> : std::true_type {};

	template<class T>
	concept EnumVariantType = IsEnumVariant<T>::value;

	template<class T>
	concept EnumVariantDefType = requires
	{
		requires EnumVariantType<typename T::value_type>;
	};

	template<class T, class VariantType>
	struct IsVariantElm : std::false_type {};
	template<class T, class... Us > requires (std::same_as<T, Us> || ... || false)
	struct IsVariantElm<T, std::variant<Us...>> : std::true_type {};

	template<class T, class U>
	concept IsEnumVariantElm = EnumType<T> && EnumVariantDefType<U> && IsVariantElm<T, typename U::value_type>::value;

	//-----------------------------------
	// EnumVariant

	template<EnumVariantDefType T>
	struct EnumVariant : T
	{
	public:
		constexpr EnumVariant() = default;

		template<IsEnumVariantElm<T> Type>
		constexpr EnumVariant(const Type& value) :
			m_value(value)
		{}

		template<IsEnumVariantElm<T> Type>
		EnumVariant& operator =(const Type& value)
		{
			this->m_value = value;
			return *this;
		}
		template<IsEnumVariantElm<T> Type>
		constexpr bool operator ==(const Type& value) const
		{
			return std::visit([value]<class U>(const U & v)
			{
				if constexpr (!std::is_same_v<Type, U>) {
					return false;
				} else {
					return v == value;
				}
			}, m_value);
		}

		template<IsEnumVariantElm<T> Type>
		constexpr bool operator !=(const Type& value) const
		{
			return !(*this == value);
		}

		template<class Func>
		constexpr decltype(auto) visit(const Func& visitor) const
		{
			return std::visit(visitor, m_value);
		}

		constexpr size_t index() const
		{
			return m_value.index();
		}

		template<IsEnumVariantElm<T> Type>
		constexpr Type as()
		{
			return std::visit([]<class U>(const U & v)
			{
				if constexpr (!std::is_same_v<Type, U>) {
					return static_cast<Type>(v);
				} else {
					return v;
				}
			}, m_value);
		}

		template<class Func>
		constexpr static decltype(auto) IndexVisit(const Func& func, size_t index)
		{
			return abyss::Meta::IndexSeqVisit([&]<size_t Seq>{
				return func.operator()<std::variant_alternative_t<Seq, typename T::value_type>>();
			}, index, std::make_index_sequence<std::variant_size_v<typename T::value_type>>());
		}
	private:

		T::value_type m_value;
	};
}