#pragma once

#include<functional>
#include<type_traits>
#include<Siv3D/Fwd.hpp>


namespace abyss
{

	template<class Func, class... Args>
	concept IsFadeFunc = std::is_invocable_v<Func, double, Args...>;

	//フェードの種類
	namespace Fade
	{
		void Default(double t);

		void SmoothCircle(double t, const s3d::RectF& rect, const s3d::Vec2& pos);
	}

	template<class Func, class... Args> 
	void FadeIn(Func func, double t, Args&& ...args) requires IsFadeFunc<Func, Args...>
	{
		func(1.0 - t, std::forward<Args>(args)...);
	}
	template<class Func, class... Args>
	void FadeOut(Func func, double t, Args&& ...args) requires IsFadeFunc<Func, Args...>
	{
		func(t, std::forward<Args>(args)...);
	}
}
