#include <abyss/components/Actor/Player/Shot/Builder.hpp>

#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/BodyUpdater.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Common/DeadOnHItReceiver.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Mover.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>

#include <abyss/components/Actor/Player/Shot/PlayerShot.hpp>
#include <abyss/components/Actor/Player/Shot/MainCollider.hpp>
#include <abyss/components/Actor/Player/Shot/EffectCtrl.hpp>
#include <abyss/components/Actor/Player/Shot/State/BaseState.hpp>

#include <abyss/params/Actor/Player/ShotParam.hpp>
#include <abyss/views/Actor/Player/Shot/ShotVM.hpp>

namespace
{
	class Presenter;
}

namespace abyss::Actor::Player::Shot
{
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos, Forward forward, double charge)
    {
		// Body
		{
			pActor->attach<Body>(pActor)
				->initPos(pos)
				.setForward(forward)
				.noneResistanced()
				.setVelocityX(forward.signH() * ShotParam::Base::Speed)
				;

			pActor->attach<BodyUpdater>(pActor);
		}

		// ショット
		auto shot = pActor->attach<PlayerShot>(charge);
		if (!shot->isBig()) {
			// Bigじゃなければ壁にあたって破壊される
			pActor->attach<DeadOnHItReceiver>(pActor);
			pActor->attach<DeadChecker>(pActor);
			pActor->attach<MapCollider>(pActor, false);
		}

		// 衝突
		{
			auto collider = pActor->attach<Collider>();
			collider->add<MainCollider>(pActor);

			pActor->attach<ColCtrl>(pActor)
				->addBranch()
				->addNode<Col::Node>(collider->main())
				.setLayer(ColSys::LayerGroup::Player)
				.attach<Col::Mover>(pActor)
				.attach<Col::Attacker>(pActor, shot->toPower())
				;
		}
		// サウンド
		{
			pActor->attach<AudioSource>(pActor);
		}

		// View
		{
			pActor->attach<VModel>()
				->setPresenter<Presenter>(pActor, shot->getType(), forward);

			pActor->attach<EffectCtrl>(pActor);
		}

		// State
		{
			pActor->attach<StateCtrl>(pActor)
				->changeState<BaseState>()
				;
		}
    }
}


namespace
{
	using namespace abyss;
	using namespace abyss::Actor;
	using namespace abyss::Actor::Player;
	using namespace abyss::Actor::Player::Shot;

	class Presenter : public IVModelPresenter<ShotVM>
	{
		ActorObj* m_pActor = nullptr;
		Ref<Body> m_body;
		std::unique_ptr<ShotVM> m_view;
	private:
		ShotVM* bind() const final
		{
			return &m_view
				->setTime(m_pActor->getTimeSec())
				.setPos(m_body->getPos())
				;
		}
		void onStart() override
		{
			m_body = m_pActor->find<Body>();
		}
	public:
		Presenter(ActorObj* pActor, PlayerShotType type, Forward forward) :
			m_pActor(pActor),
			m_view(std::make_unique<ShotVM>(type, forward))
		{}
	};
}
