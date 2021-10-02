#pragma once
#include <Siv3D/StringView.hpp>

namespace NameOf
{
	namespace detail
	{
#define NAMEOF_TO_U32_2(str) U##str
#define NAMEOF_TO_U32(str) NAMEOF_TO_U32_2(str)
#define NAMEOF_FUNCSIG NAMEOF_TO_U32(__FUNCSIG__)
		template<class Type>
		consteval s3d::StringView Signature()
		{
			return NAMEOF_FUNCSIG;
		}
		template<auto V>
		consteval s3d::StringView Signature()
		{
			return NAMEOF_FUNCSIG;
		}
#undef NAMEOF_FUNCSIG
#undef NAMEOF_TO_U32
#undef NAMEOF_TO_U32_2

		template<class Type>
		consteval s3d::StringView NameOfImplWithNamespace()
		{
			constexpr auto signature = Signature<Type>();
			constexpr auto len = signature.length();
			constexpr auto prefixLen = sizeof("class s3d::StringView __cdecl NameOf::detail::Signature<enum ") - 1;
			constexpr auto suffixLen = sizeof(">(void)") - 1;
			return signature.substr(prefixLen, len - prefixLen - suffixLen);
		}
		template<class Type>
		consteval s3d::StringView NameOfImpl()
		{
			constexpr auto result = NameOfImplWithNamespace<Type>();
			return result.substr(result.lastIndexOf(U":") + 1);
		}
		template<auto V>
		consteval s3d::StringView NameOfImplWithNamespace()
		{
			constexpr auto signature = Signature<V>();
			constexpr auto len = signature.length();
			constexpr auto prefixLen = sizeof("class s3d::StringView __cdecl NameOf::detail::Signature<") - 1;
			constexpr auto suffixLen = sizeof(">(void)") - 1;
			return signature.substr(prefixLen, len - prefixLen - suffixLen);
		}
		template<auto V>
		consteval s3d::StringView NameOfImpl()
		{
			constexpr auto result = NameOfImplWithNamespace<V>();
			return result.substr(result.lastIndexOf(U":") + 1);
		}
	}

	template<class Type>
	consteval s3d::StringView nameof()
	{
		return detail::NameOfImpl<Type>();
	}
	template<class Type>
	consteval s3d::StringView nameof_ws()
	{
		return detail::NameOfImplWithNamespace<Type>();
	}

	template<auto V>
	consteval s3d::StringView nameof()
	{
		return detail::NameOfImpl<V>();
	}
	template<auto V>
	consteval s3d::StringView nameof_ws()
	{
		return detail::NameOfImplWithNamespace<V>();
	}
}