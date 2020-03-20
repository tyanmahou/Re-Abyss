#include <abyss/commons/ActInclude.hpp>
#include <abyss/controllers/World/World.hpp>

#include <abyss/utils/Collision/Collision.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/views/Actors/Slime/SlimeVM.hpp>
#include <Siv3D.hpp>

#include "SlimeWalkState.hpp"
#include "SlimeJumpState.hpp"
namespace abyss
{
	class SlimeActor::Cencer : public IActor
	{
		Vec2 m_pos;
		bool m_onCollision = true;
		SlimeActor* m_parent;
	public:
		Cencer(SlimeActor* p):
			m_parent(p)
		{
		}
		void update(double)override
		{
			if (!m_isActive) {
				return;
			}
			if (!m_onCollision && m_parent->getMotion() == SlimeActor::Motion::Walk) {
				//m_parent->reverse();
			}
			auto isLeft = m_parent->getForward() == Forward::Left;
			if (isLeft) {
				m_pos = m_parent->getPos() + Vec2{-20, 20};
			} else {
				m_pos = m_parent->getPos() + Vec2{ 20, 20 };
			}

			m_onCollision = false;
		}
		CShape getCollider() const override
		{
			return m_pos;
		}

		void onCollisionStay(ICollider* col) override
		{
			col->accept([this](MapActor&) {
				m_onCollision = true;
			});
		}
	};

	SlimeActor::SlimeActor(const s3d::Vec2& pos, Forward forward) :
		EnemyActor(pos, forward),
		m_view(std::make_shared<SlimeVM>()),
		m_state(this)
	{
		m_hp = 10;
		m_onCollision = true;
		m_body->setMaxSpeedX(60);

		m_state.add<SlimeWalkState>(State::Walk);
		m_state.add<SlimeJumpState>(State::Jump);
	}

	void SlimeActor::start()
	{
		if (!m_cencer) {
			m_cencer = std::make_shared<Cencer>(this);
			m_pWorld->regist(m_cencer);
		}
	}

	void SlimeActor::update([[maybe_unused]]double dt)
	{
		m_state.update(dt);
	}

	void SlimeActor::draw() const
	{
		m_state.draw();
	}

	void SlimeActor::onCollisionStay(ICollider* col)
	{
		m_state.onCollisionStay(col);
	}

	CShape SlimeActor::getCollider() const
	{
		return this->region();
	}

	s3d::RectF SlimeActor::region() const
	{
		return m_body->region();
	}

	SlimeActor::Motion SlimeActor::getMotion() const
	{
		return m_motion;
	}

	void SlimeActor::reverse()
	{
		m_body->reversed();
	}

	void SlimeActor::accept(const ActVisitor& visitor)
	{
		visitor.visit(*this);
	}
	SlimeVM* SlimeActor::getBindedView() const
	{
		m_view->bind(*this);
		return m_view.get();
	}
}