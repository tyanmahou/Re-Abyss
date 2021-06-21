#pragma once
#include<Siv3D/Effect.hpp>
#include<Siv3D/Vector2D.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Actor/base/ILocator.hpp>

namespace abyss::Actor::Item::Recovery
{
	/// <summary>
	/// 回復エフェクト
	/// </summary>
	struct RecoveryEffect : s3d::IEffect
	{
	public:
		RecoveryEffect(const Ref<ILocator>& locator);

		bool update(double t) override;
	private:
		Ref<ILocator> m_locator;
		s3d::Vec2 m_pos;
		double m_startAngle = 0.0;
	};
}