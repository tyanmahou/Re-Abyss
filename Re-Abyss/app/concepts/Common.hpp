#pragma once
#include<type_traits>

namespace abyss
{
	/// <summary>
	/// フェードに使用できる関数か
	/// </summary>
	template<class Func, class... Args>
	concept IsFadeFunc = std::is_invocable_v<Func, double, Args...>;
}