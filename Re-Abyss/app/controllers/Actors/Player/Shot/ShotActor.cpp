#include "ShotActor.hpp"

#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/BodyUpdater.hpp>
#include <abyss/components/Actors/Commons/AudioSource.hpp>
#include <abyss/components/Actors/Player/Shot/Collider.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Player/Shot/State/BaseState.hpp>
#include <abyss/components/Actors/Commons/DeadOnHItReceiver.hpp>
#include <abyss/components/Actors/Commons/DeadCheacker.hpp>
#include <abyss/params/Actors/Player/ShotParam.hpp>

namespace
{
	class ViewBinder;
}
namespace abyss::Actor::Player::Shot
{
	ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward, double charge)
	{
		m_tag = Tag::Hero{} | Tag::Attacker{};

		auto shot = this->attach<PlayerShot>(charge);
		{
			this->attach<Body>(this)
				->setPos(pos)
				.setForward(forward)
				.noneResistanced()
				.setVelocityX(forward * ShotParam::Base::Speed)
				;

			this->attach<BodyUpdater>(this);
		}
		{
			this->attach<CollisionCtrl>(this)->setLayer(LayerGroup::Player);
			auto collider = this->attach<Collider>(this);
		}
		{
			this->attach<AudioSource>(this)
				->load(U"Player/Shot/player_shot.aase");
		}
		if (!shot->isBig()) {
			// Bigじゃなければ壁にあたって破壊される
			this->attach<DeadOnHItReceiver>(this);
			this->attach<DeadChecker>(this);
			this->attach<MapCollider>(this, false);
		}
		{
			this->attach<ViewCtrl<ShotVM>>()
				->createBinder<ViewBinder>(this, *shot, forward);
		}

		{
			this->attach<StateCtrl>(this)
				->changeState<BaseState>()
				;
		}
		{
			this->attach<AttackerData>(shot->toPower());
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