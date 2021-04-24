#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/components/Actors/Player/Shot/PlayerShot.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Actor::Player::Shot
{
    class ShotVM
    {
		s3d::Texture m_texture;
		PlayerShot m_shot;
		s3d::Vec2 m_pos;
		Forward m_forward;

		double m_time = 0;
	public:
		ShotVM(const PlayerShot& shot, Forward forward);
		ShotVM& setTime(double time);
		ShotVM& setPos(const s3d::Vec2& pos);

		void draw();
    };
}