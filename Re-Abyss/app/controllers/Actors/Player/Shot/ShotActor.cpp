#include "ShotActor.hpp"

#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/BodyUpdaterModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Player/Shot/ColliderModel.hpp>
#include <abyss/models/Actors/Player/Shot/State/BaseState.hpp>
#include <abyss/models/Actors/Commons/DeadOnHItReceiverModel.hpp>
#include <abyss/models/Actors/Commons/DeadCheackerModel.hpp>
#include <abyss/params/Actors/Player/ShotParam.hpp>

namespace
{
	class ViewBinder;
}
namespace abyss::Player::Shot
{
	ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward, double charge)
	{
		auto shot = this->attach<PlayerShotModel>(charge);
		{
			this->attach<BodyModel>(this)
				->setPos(pos)
				.setForward(forward)
				.noneResistanced()
				.setVelocityX(forward * ShotParam::Base::Speed)
				;

			this->attach<BodyUpdaterModel>(this);
		}
		{
			auto collider = this->attach<ColliderModel>(this);
			collider->setLayer(LayerGroup::Player);
		}
		{
			this->attach<AudioSourceModel>(this)
				->load(U"Player/Shot/player_shot.aase");
		}
		if (!shot->isBig()) {
			// Bigじゃなければ壁にあたって破壊される
			this->attach<DeadOnHItReceiverModel>(this);
			this->attach<DeadCheckerModel>(this);
		}
		{
			this->attach<ViewModel<ShotVM>>()
				->createBinder<ViewBinder>(this, *shot, forward);
		}

		{
			this->attach<StateModel>(this)
				->changeState<BaseState>()
				;
		}
		m_power = shot->toPower();
	}
	void ShotActor::start()
	{}

	bool ShotActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(static_cast<Attacker&>(*this)) || 
			visitor.visit(static_cast<IActor&>(*this));
	}
}

namespace
{
	using namespace abyss;
	using namespace abyss::Player;
	using namespace abyss::Player::Shot;

	class ViewBinder : public ViewModel<ShotVM>::IBinder
	{
		IActor* m_pActor = nullptr;
		Ref<BodyModel> m_body;
		std::unique_ptr<ShotVM> m_view;
	private:
		ShotVM* bind() const final
		{
			return &m_view
				->setTime(m_pActor->getDrawTimeSec())
				.setPos(m_body->getPos())
				.setManager(m_pActor->getManager());
		}
		void setup() override
		{
			m_body = m_pActor->find<BodyModel>();
		}
	public:
		ViewBinder(IActor* pActor, const PlayerShotModel& shot, Forward forward) :
			m_pActor(pActor),
			m_view(std::make_unique<ShotVM>(shot, forward))
		{}
	};
}