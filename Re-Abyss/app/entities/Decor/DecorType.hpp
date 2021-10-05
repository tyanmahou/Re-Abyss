#pragma once

#include <abyss/utils/Enum/EnumVariant.hpp>

namespace abyss::Decor
{
	namespace detail
	{
		class DecorTypeDef
		{
		public:
			enum class Motif
			{
				General,
				City,
			};
		public:
			enum class General
			{
				None,
				Common,
			};

			enum class City
			{
				None,
				StreetLight,
			};
		public:
			using value_type = std::variant<General, City>;
		};
	}

	class DecorType : public Enum::EnumVariant<detail::DecorTypeDef>
	{
	public:
		using EnumVariant::EnumVariant;

		DecorType& operator=(Enum::IsEnumVariantElm<DecorTypeDef> auto v)
		{
			EnumVariant::operator=(v);
			return *this;
		}

		Motif toMotif() const
		{
			return static_cast<Motif>(this->index());
		}
	private:
		using EnumVariant::index;
	};
}