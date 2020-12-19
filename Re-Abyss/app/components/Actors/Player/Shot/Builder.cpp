#include "Builder.hpp"

#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/components/Actors/Player/Shot/PlayerShot.hpp>
#include <abyss/components/Actors/Player/Shot/Collider.hpp>
#include <abyss/components/Actors/Player/Shot/State/BaseState.hpp>

#include <abyss/params/Actors/Player/ShotParam.hpp>

namespace
{
	class ViewBinder;
}

namespace abyss::Actor::Player::Shot
{
    void Builder::Build(IActor* pActor, const s3d::Vec2& pos, Forward forward, double charge)
    {
        // タグ
        pActor->setTag(Tag::Hero{} | Tag::Attacker{});

		// Body
		{
			pActor->attach<Body>(pActor)
				->setPos(pos)
				.setForward(forward)
				.noneResistanced()
				.setVelocityX(forward * ShotParam::Base::Speed)
				;

			pActor->attach<BodyUpdater>(pActor);
		}
		// 衝突
		{
			pActor->attach<CollisionCtrl>(pActor)
				->setLayer(LayerGroup::Player);

			pActor->attach<Collider>(pActor);
		}
		// サウンド
		{
			pActor->attach<AudioSource>(pActor)
				->load(U"Player/Shot/player_shot.aase");
		}
		// ショット
		auto shot = pActor->attach<PlayerShot>(charge);
		if (!shot->isBig()) {
			// Bigじゃなければ壁にあたって破壊される
			pActor->attach<DeadOnHItReceiver>(pActor);
			pActor->attach<DeadChecker>(pActor);
			pActor->attach<MapCollider>(pActor, false);
		}

		// View
		{
			pActor->attach<ViewCtrl<ShotVM>>()
				->createBinder<ViewBinder>(pActor, *shot, forward);
		}

		// State
		{
			pActor->attach<StateCtrl>(pActor)
				->changeState<BaseState>()
				;
		}

		// AttaerData
		{
			pActor->attach<AttackerData>(shot->toPower());
		}
    }
}


namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Player;
	using namespace abyss::Actor::Player::Shot;

	class ViewBinder : public ViewCtrl<ShotVM>::IBinder
	{
		IActor* m_pActor = nullptr;
		Ref<Body> m_body;
		std::unique_ptr<ShotVM> m_view;
	private:
		ShotVM* bind() const final
		{
			return &m_view
				->setTime(m_pActor->getDrawTimeSec())
				.setPos(m_body->getPos())
				.setManager(m_pActor->getManager());
		}
		void onStart() override
		{
			m_body = m_pActor->find<Body>();
		}
	public:
		ViewBinder(IActor* pActor, const PlayerShot& shot, Forward forward) :
			m_pActor(pActor),
			m_view(std::make_unique<ShotVM>(shot, forward))
		{}
	};
}