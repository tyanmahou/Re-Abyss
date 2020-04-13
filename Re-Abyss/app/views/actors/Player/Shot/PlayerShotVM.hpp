#pragma once
#include <Siv3D/Texture.hpp>
#include <abyss/models/Actors/Player/Shot/PlayerShotModel.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/commons/Fwd.hpp>
namespace abyss
{
    class PlayerShotVM
    {
		s3d::Texture m_texture;
		PlayerShotModel m_shot;
		s3d::Vec2 m_pos;
		Forward m_forward;

		ActManager* m_pManager;
	public:
		PlayerShotVM(const PlayerShotModel& shot, Forward forward);
		PlayerShotVM& setManager(ActManager* pManager);
		PlayerShotVM& setPos(const s3d::Vec2& pos);

		void addShotFiringEffect();
		void draw();
    };
}