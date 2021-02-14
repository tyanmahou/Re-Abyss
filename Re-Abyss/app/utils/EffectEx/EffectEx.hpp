#pragma once
#include <Siv3D/Effect.hpp>
#include "../Clock/Clock.hpp"

namespace abyss
{
	using IEffect = s3d::IEffect;

    /// <summary>
    /// s3d::Effectの改造
    /// </summary>
    class EffectEx
    {
    private:
        // Effectはhandleで管理しているがSivEngineとの依存が難しいのでpImplで直接実装
        class Impl;
		std::shared_ptr<Impl> m_pImpl;
	public:

		EffectEx(Clock_t timeGetter = Clock::GetNow);

		~EffectEx();

		/// <summary>
		/// 2 つの Effect が同じかどうかを返します。
		/// </summary>
		/// <param name="effect">
		/// 比較する Effect
		/// </param>
		/// <returns>
		/// 2 つの Effect が同じ場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator ==(const EffectEx& effect) const;

		/// <summary>
		/// 2 つの Effect が異なるかどうかを返します。
		/// </summary>
		/// <param name="effect">
		/// 比較する Effect
		/// </param>
		/// <returns>
		/// 2 つの Effect が異なる場合 true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool operator !=(const EffectEx& effect) const;

		[[nodiscard]] explicit operator bool() const;

		/// <summary>
		/// エフェクトが空かどうかを示します。
		/// </summary>
		[[nodiscard]] bool isEmpty() const;

		[[nodiscard]] bool hasEffects() const;

		[[nodiscard]] size_t num_effects() const;

		void add(std::unique_ptr<IEffect>&& effect) const;

		template <class EffectElement, class... Args>
		void add(Args&&... args) const
		{
			add(std::make_unique<EffectElement>(std::forward<Args>(args)...));
		}

		void add(std::function<bool(double)> f) const;

		void pause() const;

		[[nodiscard]] bool isPaused() const;

		void resume() const;

		void setSpeed(double speed) const;

		[[nodiscard]] double getSpeed() const;

		void update() const;

		void clear() const;
    };
}