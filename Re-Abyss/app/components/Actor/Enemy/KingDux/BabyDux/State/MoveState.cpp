#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/MoveState.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	constexpr double decel = 20;

	void MoveState::start()
	{
		m_startPos = m_body->getPos();

		m_body->setAccelY(400.0)
			.setMaxVelocityY(Body::DefaultMaxVelocityY)
			.setDecelX(decel);

		this->jump();
	}
	Task<> MoveState::task()
	{
		co_return;
	}
	void MoveState::update()
	{
		if (m_body->getVelocity().y > 0 && 
			m_body->getPos().y >= m_startPos.y) {
			this->jump();
		}
	}
	void MoveState::jump()
	{
		auto toPlayer = ActorUtils::ToPlayer(*m_pActor, *m_body);
		auto sign = toPlayer.x <= 0 ? -1 : 1;
		m_body->setVelocityX(sign * s3d::Math::Sqrt(2.0 * 200 * decel))
			.jumpToHeight(300.0);
	}
}