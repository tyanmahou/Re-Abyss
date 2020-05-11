#pragma once

#include <functional>
#include <Siv3D/Fwd.hpp>
#include <abyss/concepts/Common.hpp>

namespace abyss
{
	/// <summary>
	/// フェードイン
	/// </summary>
	template<class Func, class... Args> 
	void FadeIn(Func func, double t, Args&& ...args) requires IsFadeFunc<Func, Args...>
	{
		func(1.0 - t, std::forward<Args>(args)...);
	}

	/// <summary>
	/// フェードアウト
	/// </summary>
	template<class Func, class... Args>
	void FadeOut(Func func, double t, Args&& ...args) requires IsFadeFunc<Func, Args...>
	{
		func(t, std::forward<Args>(args)...);
	}

	/// <summary>
	/// フェードの種類関数群
	/// </summary>
	namespace Fade
	{
		/// <summary>
		/// 通常のフェード
		/// </summary>
		void Default(double t);

		/// <summary>
		/// 円形切り抜き
		/// </summary>
		void SmoothCircle(double t, const s3d::RectF& rect, const s3d::Vec2& pos);
	}
}
