#include "ShotActor.hpp"

#include <abyss/models/Collision/LayerGroup.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
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
			(this->attach<BodyModel>(this))
				->setPos(pos)
				.setForward(forward)
				.noneResistanced()
				.setVelocityX(forward * ShotParam::Base::Speed)
				;
		}
		{
			auto collider = this->attach<CustomColliderModel>(this);
			collider->setColFunc([this] {
				return this->getColliderCircle();
			});
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
			this->attach<ViewModel<ShotVM>>(*shot, forward)
				->createBinder<ViewBinder>(this);
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
	private:
		ShotVM* bind(ShotVM* view) const
		{
			return &view
				->setTime(m_pActor->getDrawTimeSec())
				.setPos(m_body->getPos())
				.setManager(m_pActor->getManager());
		}
		void setup() override
		{
			m_body = m_pActor->find<BodyModel>();
		}
	public:
		ViewBinder(IActor* pActor) :
			m_pActor(pActor)
		{}
	};
}