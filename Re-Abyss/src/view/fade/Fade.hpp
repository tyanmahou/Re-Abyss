#pragma once

#include<functional>
#include<Siv3D/Fwd.hpp>
#include "../../util/TypeTraits.hpp"

namespace abyss
{
	//フェードの種類
	namespace Fade
	{
		void Default(double t);

		void SmoothCircle(double t, const s3d::RectF& rect, const s3d::Vec2& pos);
	}

	template<class Func, class... Args>
	auto FadeIn(Func func, double t, Args&& ...args)->std::enable_if_t <is_invocable_v<Func, double, Args...>>
	{
		func(1.0 - t, std::forward<Args>(args)...);
	}
	template<class Func, class... Args>
	auto FadeOut(Func func, double t, Args&& ...args)->std::enable_if_t <is_invocable_v<Func, double, Args...>>
	{
		func(t, std::forward<Args>(args)...);
	}

	template<class ...Args>
	using FadeArgsFunc_t = void(*)(double, Args...);

	using FadeFunc_t = FadeArgsFunc_t<>;
}
