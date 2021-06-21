#pragma once
#include<Siv3D/Effect.hpp>
#include<Siv3D/Vector2D.hpp>

namespace abyss::Actor::Item::Recovery
{
	/// <summary>
	/// 回復エフェクト
	/// </summary>
	struct RecoveryEffect : s3d::IEffect
	{
	public:
		RecoveryEffect(const s3d::Vec2& pos);

		bool update(double t) override;
	private:
		s3d::Vec2 m_pos;
		double m_startAngle = 0.0;
	};
}