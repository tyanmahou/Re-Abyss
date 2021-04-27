#include "ActorObj.hpp"
#include <abyss/components/Actors/Commons/ClockCtrl.hpp>
#include <abyss/components/Actors/base/IUpdate.hpp>
#include <abyss/components/Actors/base/IPostUpdate.hpp>
#include <abyss/components/Actors/base/IMove.hpp>
#include <abyss/components/Actors/base/IPrePhysics.hpp>
#include <abyss/components/Actors/base/IPostPhysics.hpp>
#include <abyss/components/Actors/base/IPreCollision.hpp>
#include <abyss/components/Actors/base/IPostCollision.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>
#include <abyss/components/Actors/base/IDraw.hpp>
#include <abyss/components/Actors/base/IPreDraw.hpp>

namespace abyss::Actor
{
	ActorObj::ActorObj()
	{
		m_clock = this->attach<ClockCtrl>();
	}
	void ActorObj::updateDeltaTime(double worldDt) const
	{
		m_clock->updateDeltaTime(worldDt);
	}
	void ActorObj::update()
	{
		m_clock->updateUpdateTime();
		for (auto&& com : this->finds<IUpdate>()) {
			com->onUpdate();
		}
	}
	void ActorObj::postUpdate()
	{
		for (auto&& com : this->finds<IPostUpdate>()) {
			com->onPostUpdate();
		}
	}
	void ActorObj::move()
	{
		for (auto&& com : this->finds<IMove>()) {
			com->onMove();
		}
	}
	void ActorObj::prePhysics()
	{
		for (auto&& com : this->finds<IPrePhysics>()) {
			com->onPrePhysics();
		}
	}
	void ActorObj::postPhysics()
	{
		for (auto&& com : this->finds<IPostPhysics>()) {
			com->onPostPhysics();
		}
	}
	void ActorObj::preCollision()
	{
		for (auto&& com : this->finds<IPreCollision>()) {
			com->onPreCollision();
		}
	}

	void ActorObj::postCollision()
	{
		for (auto&& com : this->finds<IPostCollision>()) {
			com->onPostCollision();
		}
	}

	void ActorObj::lastUpdate()
	{
		for (auto&& com : this->finds<ILastUpdate>()) {
			com->onLastUpdate();
		}
	}
	void ActorObj::draw() const
	{
		m_clock->updateDrawTime();
		for (auto&& com : this->finds<IPreDraw>()) {
			com->onPreDraw();
		}
		for (auto&& com : this->finds<IDraw>()) {
			com->onDraw();
		}
	}
	s3d::Microseconds ActorObj::getUpdateTime() const
	{
		return m_clock->getUpdateTime();
	}
	double ActorObj::getUpdateTimeSec() const
	{
		return m_clock->getUpdateTimeSec();
	}
    std::function<s3d::Microseconds()> ActorObj::getUpdateClock() const
    {
		return [this] {return this->getUpdateTime(); };
    }
	s3d::Microseconds ActorObj::getDrawTime() const
	{
		return m_clock->getDrawTime();
	}
	double ActorObj::getDrawTimeSec() const
	{
		return m_clock->getDrawTimeSec();
	}
	std::function<s3d::Microseconds()> ActorObj::getDrawClock() const
	{
		return [this] {return this->getDrawTime(); };
	}
	double ActorObj::deltaTime() const
	{
		return m_clock->getDeltaTime();
	}
}