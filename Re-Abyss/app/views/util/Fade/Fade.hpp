#pragma once
#include <functional>
#include <Siv3D/Rect.hpp>
#include <abyss/commons/Concepts.hpp>
#include <abyss/utils/Singleton/DynamicSingleton.hpp>

namespace abyss
{
    /// <summary>
    /// フェードに使用できる関数か
    /// </summary>
    template<class Func, class... Args>
    concept FadeFunctionaly = std::invocable<Func, double, Args...>;

	/// <summary>
	/// フェードイン
	/// </summary>
	template<class Func, class... Args> 
	void FadeIn(Func func, double t, Args&& ...args) requires FadeFunctionaly<Func, Args...>
	{
		func(1.0 - t, std::forward<Args>(args)...);
	}

	/// <summary>
	/// フェードアウト
	/// </summary>
	template<class Func, class... Args>
	void FadeOut(Func func, double t, Args&& ...args) requires FadeFunctionaly<Func, Args...>
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

        /// <summary>
        /// 色指定
        /// </summary>
        /// <param name="color"></param>
        static void SetColor(const s3d::ColorF& color);
	private:
		Fade();
		~Fade();
	private:
		class Impl;
		std::unique_ptr<Impl> m_pImpl;
	};
}
