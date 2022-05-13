#pragma once
#include <functional>
#include <Siv3D/Rect.hpp>
#include <abyss/concepts/Common.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

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
	class Fade : protected DynamicSingleton<Fade>
	{
		friend class DynamicSingleton<Fade>;
	public:
		/// <summary>
		/// 通常のフェード
		/// </summary>
		static void Default(double t);

		/// <summary>
		/// 円形切り抜き
		/// </summary>
		static void IrisOutRect(double t, const s3d::Vec2& pos, const s3d::RectF& rect);

		static void IrisOut(double t, const s3d::Vec2& pos);
	private:
		Fade();
		~Fade();
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
