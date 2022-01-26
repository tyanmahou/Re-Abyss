#pragma once
#include <utility>

namespace abyss::Meta
{
	template<class Func, size_t... Seq>
	constexpr static decltype(auto) IndexSeqVisit(const Func& func, size_t index, std::index_sequence<Seq...>)
	{
		using return_type = decltype(func.operator()<0>());
		if constexpr (std::is_void_v<return_type>) {
			bool find = false;
			find = ((index == Seq ? (func.operator()<Seq>(), true) : false) || ...);
		} else {
			return_type ret{};
			bool find = false;
			find = ((index == Seq ? (ret = func.operator()<Seq>(), true) : false) || ...);
			return ret;
		}
	}
}