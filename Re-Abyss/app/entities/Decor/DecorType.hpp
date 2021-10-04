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
		public:
			template<class T>
			static decltype(auto) Visit(T func, Motif motif)
			{
				switch (motif) {
				case Motif::General:
					return func.operator()<General>();
				case Motif::City:
					return func.operator()<City>();
				default:
					break;
				}
				return func.operator()<void>();
			}
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

		Motif getMotif() const
		{
			return static_cast<Motif>(this->index());
		}
	private:
		using EnumGroup::index;
	};
}