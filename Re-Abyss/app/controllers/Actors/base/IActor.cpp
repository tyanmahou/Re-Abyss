#include "IActor.hpp"
#include <abyss/models/Actors/Commons/ActorTimeModel.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>

namespace abyss
{
	IActor::IActor()
	{
		m_time = this->addComponent<ActorTimeModel>();
	}
	void IActor::updateTime(double worldDt) const
	{
		m_time->update(worldDt);
	}
	void IActor::setup() const
	{
		m_components.setup();
	}
	void IActor::update()
	{
		double dt = m_time->getDeltaTime();
		for (auto&& com : this->findComponents<IUpdateModel>()) {
			com->onUpdate(dt);
		}
		this->update(dt);
	}
	void IActor::lastUpdate()
	{
		this->lastUpdate(m_time->getDeltaTime());
	}
	bool IActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
}