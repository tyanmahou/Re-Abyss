#pragma once
#include <Siv3D/IEffect.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss
{
	struct BreathEffect : s3d::IEffect
	{
	private:
		s3d::Vec2 m_pos;
	public:

		BreathEffect(const s3d::Vec2& pos);

		bool update(double t)override;
	};
}