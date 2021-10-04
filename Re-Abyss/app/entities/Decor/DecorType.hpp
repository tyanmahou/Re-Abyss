#pragma once

#include <abyss/utils/Enum/EnumGroup.hpp>

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

	class DecorType : public Enum::EnumGroup<detail::DecorTypeDef>
	{
	public:
		using EnumGroup::EnumGroup;

		DecorType& operator=(Enum::IsEnumGroupElm<DecorTypeDef> auto v)
		{
			EnumGroup::operator=(v);
			return *this;
		}

		Motif toMotif() const
		{
			return static_cast<Motif>(this->index());
		}
	private:
		using EnumGroup::index;
	};
}