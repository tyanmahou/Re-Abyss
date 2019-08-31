#pragma once
#include<utility>

namespace abyss
{
	template<class Head, class... Tail>
	struct overloaded_impl : Head, overloaded_impl<Tail...>
	{
		overloaded_impl(Head h, Tail... tail) :
			Head(std::forward<Head>(h)),
			overloaded_impl<Tail...>(std::forward<Tail>(tail)...)
		{}
		using Head::operator();
		using overloaded_impl<Tail...>::operator();
	};
	template<class Last>
	struct overloaded_impl<Last> : Last
	{
		overloaded_impl(Last last) :
			Last(std::forward<Last>(last))
		{}
		using Last::operator();
	};

	template<class... Type>
	overloaded_impl<Type...> overloaded(Type&& ... func)
	{
		return overloaded_impl<Type... >{std::forward<Type>(func)...};
	};
}