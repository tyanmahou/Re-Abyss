#include "IActor.hpp"
#include <abyss/components/Actors/Commons/ActorTime.hpp>
#include <abyss/components/Actors/base/IUpdate.hpp>
#include <abyss/components/Actors/base/IMove.hpp>
#include <abyss/components/Actors/base/IPrePhysics.hpp>
#include <abyss/components/Actors/base/ILastPhysics.hpp>
#include <abyss/models/Actors/base/ILastUpdateModel.hpp>
#include <abyss/models/Actors/base/IDrawModel.hpp>
#include <abyss/models/Actors/base/IPreDrawModel.hpp>

using namespace abyss::Actor;

namespace abyss
{
	IActor::IActor()
	{
		m_time = this->attach<ActorTime>();
	}
	void IActor::updateDeltaTime(double worldDt) const
	{
		m_time->updateDeltaTime(worldDt);
	}
	void IActor::setup() const
	{
		m_components.setup();
	}
	void IActor::start()
	{
		m_components.start();
	}
	void IActor::update()
	{
		m_time->updateUpdateTime();
		double dt = m_time->getDeltaTime();
		for (auto&& com : this->finds<IUpdate>()) {
			com->onUpdate(dt);
		}
	}
	void IActor::move()
	{
		double dt = m_time->getDeltaTime();
		for (auto&& com : this->finds<IMove>()) {
			com->onMove(dt);
		}
	}
	void IActor::prePhysics()
	{
		for (auto&& com : this->finds<IPrePhysics>()) {
			com->onPrePhysics();
		}
	}
	void IActor::lastPhysics()
	{
		for (auto&& com : this->finds<ILastPhysics>()) {
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