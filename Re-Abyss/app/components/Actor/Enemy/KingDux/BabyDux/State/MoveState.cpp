#include <abyss/components/Actor/Enemy/KingDux/BabyDux/State/MoveState.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/KingDux/BabyDuxParam.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	void MoveState::start()
	{
		m_startPos = m_body->getPos();
	}
	Task<> MoveState::task()
	{
		while (true) {
			// ため
			m_body->noneResistanced();
			TimeLite::Timer timer{ BabyDuxParam::Move::ChargeTimeSec };
			m_startPos = m_body->getPos();
			while (!timer.isEnd()) {
				timer.update(m_pActor->deltaTime());

				auto rate = timer.rate();
				rate = s3d::EaseInOutQuad(rate);
				double offsetY = s3d::Math::Lerp(0, BabyDuxParam::Move::ChargeOffs, rate);
				auto targetPos = m_startPos;
				targetPos.y += offsetY;

				m_body->moveToPos(targetPos, m_pActor->deltaTime());
				co_yield{};
			}

			// ジャンプ
			this->jump();

			while (true) {
				if (m_body->getVelocity().y > 0 && m_body->getPos().y >= m_startPos.y) {
					break;
				}
				co_yield{};
			}
		}
		co_return;
	}
	void MoveState::update()
	{
	}
	void MoveState::jump()
	{
		auto toPlayer = ActorUtils::ToPlayer(*m_pActor, *m_body);
		auto sign = toPlayer.x <= 0 ? -1 : 1;
		m_body->setAccelY(BabyDuxParam::Move::Gravity)
			.setMaxVelocityY(BabyDuxParam::Move::MaxSpeedY)
			.setDecelX(BabyDuxParam::Move::DecelX)
			.setVelocityX(sign * s3d::Math::Sqrt(2.0 * BabyDuxParam::Move::MoveX * BabyDuxParam::Move::DecelX))
			.jumpToHeight(BabyDuxParam::Move::JumpHeight);
	}
}