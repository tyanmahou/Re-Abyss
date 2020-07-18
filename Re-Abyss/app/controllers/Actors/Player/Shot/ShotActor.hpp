#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Attacker.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Player/Shot/PlayerShotModel.hpp>
#include <abyss/models/Actors/base/OldStateModel.hpp>

namespace abyss::Player::Shot
{
	class ShotVM;

	class ShotActor : 
		public IActor,
		public Attacker
	{
	public:
		enum State
		{
			Base,
		};
	private:
		Ref<PlayerShotModel> m_shot;
		Ref<BodyModel> m_body;
		Ref<OldStateModel<ShotActor>> m_state;
		std::shared_ptr<ShotVM> m_view;
	public:
		ShotActor(const s3d::Vec2& pos, Forward forward, double charge);
		void start() override;

		s3d::Circle getColliderCircle() const;

		bool accept(const ActVisitor& visitor) override;

		ShotVM* getBindedView()const;
	};
}