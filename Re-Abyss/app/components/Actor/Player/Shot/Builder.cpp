#include "Builder.hpp"

#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/AttackerData.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/BodyUpdater.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>
#include <abyss/components/Actor/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actor/Commons/MapCollider.hpp>
#include <abyss/components/Actor/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actor/Commons/DeadCheacker.hpp>
#include <abyss/components/Actor/Commons/VModel.hpp>
#include <abyss/components/Actor/Player/Shot/PlayerShot.hpp>
#include <abyss/components/Actor/Player/Shot/Collider.hpp>
#include <abyss/components/Actor/Player/Shot/EffectCtrl.hpp>
#include <abyss/components/Actor/Player/Shot/State/BaseState.hpp>

#include <abyss/params/Actor/Player/ShotParam.hpp>
#include <abyss/views/Actor/Player/Shot/ShotVM.hpp>

namespace
{
	class ViewBinder;
}

namespace abyss::Actor::Player::Shot
{
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos, Forward forward, double charge)
    {
        // タグ
        pActor->setTag(Tag::Hero{} | Tag::Attacker{});

		// Body
		{
			pActor->attach<Body>(pActor)
				->initPos(pos)
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
			pActor->attach<VModel>()
				->setBinder<ViewBinder>(pActor, shot->getType(), forward);

			pActor->attach<EffectCtrl>(pActor);
		}

		// State
		{
			pActor->attach<StateCtrl>(pActor)
				->changeState<BaseState>()
				;
		}

		// AttaerData
		{
			pActor->attach<AttackerData>(pActor, shot->toPower());
		}
    }
}


namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Player;
	using namespace abyss::Actor::Player::Shot;

	class ViewBinder : public IVModelBinder<ShotVM>
	{
		ActorObj* m_pActor = nullptr;
		Ref<Body> m_body;
		std::unique_ptr<ShotVM> m_view;
	private:
		ShotVM* bind() const final
		{
			return &m_view
				->setTime(m_pActor->getDrawTimeSec())
				.setPos(m_body->getPos())
				;
		}
		void onStart() override
		{
			m_body = m_pActor->find<Body>();
		}
	public:
		ViewBinder(ActorObj* pActor, PlayerShotType type, Forward forward) :
			m_pActor(pActor),
			m_view(std::make_unique<ShotVM>(type, forward))
		{}
	};
}