#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/models/Actors/Player/Shot/PlayerShotModel.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss::Player::Shot
{
    class ShotVM
    {
		s3d::Texture m_texture;
		PlayerShotModel m_shot;
		s3d::Vec2 m_pos;
		Forward m_forward;

		double m_time = 0;
		Manager* m_pManager;
	public:
		ShotVM(const PlayerShotModel& shot, Forward forward);
		ShotVM& setTime(double time);
		ShotVM& setManager(Manager* pManager);
		ShotVM& setPos(const s3d::Vec2& pos);

		void addShotFiringEffect();
		void draw();
    };
}