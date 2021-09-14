#pragma once
#include<Siv3D/Effect.hpp>
#include<Siv3D/Vector2D.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Actor/Commons/ILocator.hpp>

namespace abyss::Actor::Item::Recovery
{
	/// <summary>
	/// 回復エフェクト
	/// </summary>
	struct RecoveryEffect : s3d::IEffect
	{
	private:
		struct Impl;
	public:
		RecoveryEffect(const Ref<ILocator>& locator);

		bool update(double t) override;
	private:
		std::unique_ptr<Impl> m_pImpl;
	};
}