#pragma once
#include<concepts>

namespace abyss
{
	/// <summary>
	/// フェードに使用できる関数か
	/// </summary>
	template<class Func, class... Args>
	concept FadeFunctionaly = std::invocable<Func, double, Args...>;
}
