#pragma once
#include "EnumTraits.hpp"
#include <variant>

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
	concept EnumGroupDefType = requires
	{
		requires EnumVariantType<typename T::value_type>;
	};

	template<class T, class VariantType>
	struct IsVariantElm : std::false_type {};
	template<class T, class... Us > requires (std::same_as<T, Us> || ... || false)
	struct IsVariantElm<T, std::variant<Us...>> : std::true_type {};

	template<class T, class U>
	concept IsEnumGroupElm = EnumType<T> && EnumGroupDefType<U> && IsVariantElm<T, typename U::value_type>::value;

	//-----------------------------------
	// EnumGroup

	template<EnumGroupDefType T>
	struct EnumGroup : T
	{
	public:
		constexpr EnumGroup() = default;

		template<IsEnumGroupElm<T> Type>
		constexpr EnumGroup(const Type& value) :
			m_value(value)
		{}

		template<IsEnumGroupElm<T> Type>
		EnumGroup& operator =(const Type& value)
		{
			this->m_value = value;
			return *this;
		}
		template<IsEnumGroupElm<T> Type>
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

		template<IsEnumGroupElm<T> Type>
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

		template<IsEnumGroupElm<T> Type>
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
			return IndexVisit(func, index, std::make_index_sequence<std::variant_size_v<typename T::value_type>>());
		}
	private:

		template<class Func, size_t... Seq>
		constexpr static decltype(auto) IndexVisit(const Func& func, size_t index, std::index_sequence<Seq...>)
		{
			using return_type = decltype(func.operator()<void>());
			if constexpr (std::is_void_v<return_type>) {
				bool find = false;
				find = ((index == Seq ? (func.operator()<std::variant_alternative_t<Seq, typename T::value_type>>(), true) : false) || ...);
			} else {
				return_type ret{};
				bool find = false;
				find = ((index == Seq ? (ret = func.operator()<std::variant_alternative_t<Seq, typename T::value_type>>(), true) : false) || ...);
				return ret;
			}
		}

		T::value_type m_value;
	};
}