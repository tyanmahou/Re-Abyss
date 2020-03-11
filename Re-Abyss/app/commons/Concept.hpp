#pragma once
#include<type_traits>
#include <abyss/models/actors/base/IActor.hpp>

namespace abyss
{
	/// <summary>
	/// アクターか
	/// </summary>
    template<class Type>
    concept IsActor = std::is_base_of_v<IActor, Type>;

	/// <summary>
	/// フェードに使用できる関数か
    /// </summary>
	template<class Func, class... Args>
	concept IsFadeFunc = std::is_invocable_v<Func, double, Args...>;
}