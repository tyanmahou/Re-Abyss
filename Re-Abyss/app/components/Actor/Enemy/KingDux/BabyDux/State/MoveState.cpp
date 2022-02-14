#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/MoveState.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/KingDux/BabyDuxParam.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	void MoveState::start()
	{
		m_startPos = m_body->getPos();

		m_body->setAccelY(BabyDuxParam::Move::Gravity)
			.setMaxVelocityY(BabyDuxParam::Move::MaxSpeedY)
			.setDecelX(BabyDuxParam::Move::DecelX);

		this->jump();
	}
	Task<> MoveState::task()
	{
		co_return;
	}
	void MoveState::update()
	{
		if (m_body->getVelocity().y > 0 && 
			m_body->getPos().y >= m_startPos.y + BabyDuxParam::Move::FallLimitOffs) {
			this->jump();
		}
	}
	void MoveState::jump()
	{
		auto toPlayer = ActorUtils::ToPlayer(*m_pActor, *m_body);
		auto sign = toPlayer.x <= 0 ? -1 : 1;
		m_body->setVelocityX(sign * s3d::Math::Sqrt(2.0 * BabyDuxParam::Move::MoveX * BabyDuxParam::Move::DecelX))
			.jumpToHeight(BabyDuxParam::Move::JumpHeight);
	}
}