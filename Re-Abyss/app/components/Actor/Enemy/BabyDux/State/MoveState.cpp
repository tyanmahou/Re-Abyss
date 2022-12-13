#include <abyss/components/Actor/Enemy/BabyDux/State/MoveState.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/params/Actor/Enemy/BabyDux/Param.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
	void MoveState::start()
	{
		m_startPos = m_body->getPos();
	}
	Fiber<> MoveState::task()
	{
		while (true) {
			// ため
			co_await taskCharge();

			// ジャンプ
			co_await taskJump();
		}
		co_return;
	}
	void MoveState::update()
	{
	}

	Fiber<> MoveState::taskCharge()
	{
		m_startPos = m_body->getPos();
		m_body->noneResistanced();
        m_motion->set(Motion::Charge);
		TimeLite::Timer timer{ Param::Move::ChargeTimeSec };
		while (!timer.isEnd()) {
			timer.update(m_pActor->deltaTime());

			auto rate = timer.rate();
			rate = s3d::EaseOutQuad(rate);
			double offsetY = s3d::Math::Lerp(0, Param::Move::ChargeOffs, rate);
			auto targetPos = m_startPos;
			targetPos.y += offsetY;

			m_body->moveToPos(targetPos, m_pActor->deltaTime());
            m_motion->setAnimeTime(timer.rate());
            co_yield{};
		}
    }
	Fiber<> MoveState::taskJump()
	{
		auto toPlayer = ActorUtils::ToPlayer(*m_pActor, *m_body);
		auto sign = toPlayer.x <= 0 ? -1 : 1;
		m_body->setAccelY(Param::Move::Gravity)
			.setMaxVelocityY(Param::Move::MaxSpeedY)
			.setDecelX(Param::Move::DecelX)
			.setVelocityX(sign * s3d::Math::Sqrt(2.0 * Param::Move::MoveX * Param::Move::DecelX))
			.jumpToHeight(Param::Move::JumpHeight);
        m_motion->set(Motion::Jump);
        auto jumpSpeed = Abs(m_body->getVelocity().y);
		while (true) {
            auto vy = m_body->getVelocity().y;
            if (vy < 0) {
                m_motion->setAnimeTime(1.0 - Saturate(Abs(vy) / jumpSpeed));
            } else if (vy > 0 && m_body->getPos().y >= m_startPos.y - Param::Move::JumpHeight / 2.0) {
                m_motion->set(Motion::Wait);
            }
			if (vy > 0 && m_body->getPos().y >= m_startPos.y) {
				break;
			}
			co_yield{};
		}
        m_motion->set(Motion::Wait);
	}
}
