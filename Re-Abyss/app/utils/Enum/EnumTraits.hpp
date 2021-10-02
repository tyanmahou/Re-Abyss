#pragma once
#include <concepts>
#include <abyss/utils/NameOf/NameOf.hpp>

namespace Enum
{
	template<class E>
	concept EnumType = std::is_enum_v<E>;

	template<class E>
	concept EnumDefaultable = EnumType<E> && requires{
		{ E::Default }->std::same_as<E>;
	};

	namespace detail
	{
		template<EnumType E>
		consteval E GetDefault()
		{
			if constexpr (EnumDefaultable<E>) {
				return E::Default;
			} else {
				return static_cast<E>(0);
			}
		}
		template<EnumType E, int ...Seq>
		constexpr s3d::StringView ToStrSeqImpl(E v, std::integer_sequence<int, Seq...>)
		{
			using NameOf::nameof;

			constexpr auto len = static_cast<int>(sizeof...(Seq));

			s3d::StringView result{ nameof <GetDefault<E>()> () };
			bool find = ((v == static_cast<E>(Seq - len) ? (result = nameof<static_cast<E>(Seq - len)>(), true) : false) || ...);
			find = find || ((v == static_cast<E>(Seq) ? (result = nameof<static_cast<E>(Seq)>(), true) : false) || ...);

			return result;
		}
		template<EnumType E>
		constexpr s3d::StringView ToStrSeq(E v)
		{
			return ToStrSeqImpl(v, std::make_integer_sequence<int, 256>());
		}

		template<EnumType E, int ...Seq>
		constexpr E ParseSeqImpl(const s3d::StringView sv, std::integer_sequence<int, Seq...>)
		{
			using NameOf::nameof;
			constexpr auto len = static_cast<int>(sizeof...(Seq));

			E result = GetDefault<E>();
			bool find = ((sv == nameof<static_cast<E>(Seq - len)>() ? (result = static_cast<E>(Seq - len), true) : false) || ...);
			find = find || ((sv == nameof<static_cast<E>(Seq)>() ? (result = static_cast<E>(Seq), true) : false) || ...);

			return result;
		}
		template<EnumType E>
		constexpr E ParseSeq(const s3d::StringView sv)
		{
			return ParseSeqImpl<E>(sv, std::make_integer_sequence<int, 256>());
		}
	}

	template<EnumType E>
	struct EnumTraits
	{
		constexpr s3d::StringView ToStrView(E v)
		{
			return default_(v);
		}
		constexpr E Parse(const s3d::StringView sv)
		{
			return default_(sv);
		}
	private:
		constexpr s3d::StringView default_(E v)
		{
			return detail::ToStrSeq(v);
		}
		constexpr E default_(const s3d::StringView sv)
		{
			return detail::ParseSeq<E>(sv);
		}
	};

	/// <summary>
	/// 列挙型の値を文字列に変換
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	template<EnumType E>
	s3d::String ToStr(E v)
	{
		return s3d::String(EnumTraits<E>{}.ToStrView(v));
	}

	/// <summary>
	/// 列挙型の値を文字列に変換
	/// </summary>
	/// <param name="v"></param>
	/// <returns></returns>
	template<EnumType E>
	constexpr s3d::StringView ToStrView(E v)
	{
		return EnumTraits<E>{}.ToStrView(v);
	}

	/// <summary>
	/// 文字列から列挙型に変換
	/// </summary>
	/// <param name="sv"></param>
	/// <returns></returns>
	template<EnumType E>
	constexpr E Parse(const s3d::StringView sv)
	{
		return EnumTraits<E>{}.Parse(sv);
	}
	template<EnumType E>
	constexpr E Parse(const s3d::String& str)
	{
		return Parse<E>(s3d::StringView(str));
	}
}