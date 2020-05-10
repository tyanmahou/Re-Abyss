#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>
#include <abyss/commons/LayerGroup.hpp>
#include <abyss/models/Actors/Commons/CustomColliderModel.hpp>
#include <abyss/models/Actors/Player/Shot/State/BaseState.hpp>
#include <abyss/params/Actors/Player/ShotParam.hpp>

namespace abyss::Player::Shot
{
	ShotActor::ShotActor(const s3d::Vec2& pos, Forward forward, double charge)
	{
		m_shot = this->addComponent<PlayerShotModel>(charge);
		(m_state = this->addComponent<exp::StateModel<ShotActor>>(this))
			->add<BaseState>(State::Base);

		(m_body = this->addComponent<BodyModel>(this))
			->setPos(pos)
			.setForward(forward)
			.noneResistanced()
			.setVelocityX(forward * ShotParam::Base::Speed)
			;

		m_power = m_shot->toPower();
		m_view = std::make_shared<ShotVM>(*m_shot, forward);

		auto collider = this->addComponent<CustomColliderModel>(this);
		collider->setColFunc([this] {
			return this->getColliderCircle();
		});
		collider->setLayer(LayerGroup::Player);
	}
	void ShotActor::start()
	{}

	s3d::Circle ShotActor::getColliderCircle() const
	{
		return s3d::Circle(m_body->getPos(), m_shot->toRadius());
	}

	bool ShotActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(static_cast<Attacker&>(*this)) || 
			visitor.visit(static_cast<IActor&>(*this));
	}
	ShotVM* ShotActor::getBindedView() const
	{
		if (!m_view) {
			return nullptr;
		}
		return &m_view->setPos(m_body->getPos()).setManager(m_pManager);
	}
}