#include "IActor.hpp"
#include <abyss/models/Actors/Commons/ActorTimeModel.hpp>
#include <abyss/models/Actors/base/IUpdateModel.hpp>
#include <abyss/models/Actors/base/IPrePhysicsModel.hpp>
#include <abyss/models/Actors/base/ILastPhysicsModel.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/models/Actors/base/IPreDrawModel.hpp>

namespace abyss
{
	IActor::IActor()
	{
		m_time = this->attach<ActorTimeModel>();
	}
	void IActor::updateDeltaTime(double worldDt) const
	{
		m_time->updateDeltaTime(worldDt);
	}
	void IActor::setup() const
	{
		m_components.setup();
	}
	void IActor::update()
	{
		m_time->updateUpdateTime();
		double dt = m_time->getDeltaTime();
		for (auto&& com : this->finds<IUpdateModel>()) {
			com->onUpdate(dt);
		}
	}
	void IActor::prePhysics()
	{
		for (auto&& com : this->finds<IPrePhysicsModel>()) {
			com->onPrePhysics();
		}
	}
	void IActor::lastPhysics()
	{
		for (auto&& com : this->finds<ILastPhysicsModel>()) {
			com->onLastPhysics();
		}
	}
	void IActor::lastUpdate()
	{
		for (auto&& com : this->finds<ILastUpdateModel>()) {
			com->onLastUpdate();
		}
	}
	void IActor::draw() const
	{
		m_time->updateDrawTime();
		for (auto&& com : this->finds<IPreDrawModel>()) {
			com->onPreDraw(m_time->getDeltaTime());
		}
		for (auto&& com : this->finds<IDrawModel>()) {
			com->onDraw();
		}
	}
	bool IActor::accept(const ActVisitor& visitor)
	{
		return visitor.visit(*this);
	}
	s3d::Microseconds IActor::getUpdateTime() const
	{
		return m_time->getUpdateTime();
	}
	double IActor::getUpdateTimeSec() const
	{
		return m_time->getUpdateTimeSec();
	}
    std::function<s3d::Microseconds()> IActor::getUpdateTimer() const
    {
		return [this] {return this->getUpdateTime(); };
    }
	s3d::Microseconds IActor::getDrawTime() const
	{
		return m_time->getDrawTime();
	}
	double IActor::getDrawTimeSec() const
	{
		return m_time->getDrawTimeSec();
	}
	std::function<s3d::Microseconds()> IActor::getDrawTimer() const
	{
		return [this] {return this->getDrawTime(); };
	}
}