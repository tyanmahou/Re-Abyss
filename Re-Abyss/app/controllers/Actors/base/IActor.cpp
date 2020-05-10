#include "IActor.hpp"
#include <abyss/models/Actors/Commons/ActorTimeModel.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
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
		double dt = m_time->getDeltaTime();
		for (auto&& com : this->findComponents<ILastUpdateModel>()) {
			com->onLastUpdate(dt);
		}
		this->lastUpdate(dt);
	}
	void IActor::draw() const
	{
		for (auto&& com : this->findComponents<IDrawModel>()) {
			com->onDraw();
		}
	}
	bool IActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
}