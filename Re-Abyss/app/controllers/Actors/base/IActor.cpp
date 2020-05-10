#include "IActor.hpp"
#include <abyss/models/Actors/Commons/ActorTimeModel.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
namespace abyss
{
	IActor::IActor()
	{
		m_time = this->attach<ActorTimeModel>();
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
		for (auto&& com : this->finds<IUpdateModel>()) {
			com->onUpdate(dt);
		}
	}
	void IActor::lastUpdate()
	{
		double dt = m_time->getDeltaTime();
		for (auto&& com : this->finds<ILastUpdateModel>()) {
			com->onLastUpdate(dt);
		}
	}
	void IActor::draw() const
	{
		for (auto&& com : this->finds<IDrawModel>()) {
			com->onDraw();
		}
	}
	bool IActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
    s3d::Microseconds IActor::getTime() const
    {
		return m_time->getTime();
    }
}