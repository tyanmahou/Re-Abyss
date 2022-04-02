#pragma once
#include <abyss/utils/TexturePacker/TexturePacker.hpp>

namespace abyss::Effect::Actor
{
	class EnemyDeadVM
	{
	public:
		EnemyDeadVM();
		
		EnemyDeadVM& setPos(const s3d::Vec2& pos);
		EnemyDeadVM& setAnimRate(double animeRate);

		void draw() const;

	private:
		TexturePacker m_texture;
		s3d::Vec2 m_pos;
		double m_animeRate = 0;
	};
}