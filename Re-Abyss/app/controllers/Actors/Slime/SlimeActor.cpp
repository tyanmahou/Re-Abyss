#include "State/SlimeWalkState.hpp"
#include "State/SlimeJumpState.hpp"
#include "Senser/SlimeSenser.hpp"

#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/Slime/SlimeVM.hpp>
#include <abyss/debug/DebugManager/DebugManager.hpp>

namespace abyss
{
	SlimeActor::SlimeActor(const s3d::Vec2& pos, Forward forward) :
		EnemyActor(pos, forward),
		m_view(std::make_shared<SlimeVM>()),
		m_state(this)
	{
		m_hp = 10;
		m_body.setMaxSpeedX(60);

		m_state.add<SlimeWalkState>(State::Walk);
		m_state.add<SlimeJumpState>(State::Jump);
	}

	void SlimeActor::start()
	{
		if (!m_senser) {
			m_senser = m_pWorld->create<SlimeSenser>(this);
		}
	}

	void SlimeActor::update([[maybe_unused]]double dt)
	{
		m_state.update(dt);
	}

	void SlimeActor::draw() const
	{
		m_state.draw();

#if ABYSS_DEBUG
		if (DebugManager::IsDrawColider()) {
			this->region().draw(s3d::ColorF(1, 0, 0, 0.5));
		}
#endif
	}

	void SlimeActor::onCollisionStay(ICollider* col)
	{
		m_state.onCollisionStay(col);
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
	bool SlimeActor::isWalk() const
	{
		return m_state.getState() == State::Walk;
	}
}