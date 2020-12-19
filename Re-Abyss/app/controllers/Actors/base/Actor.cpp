#include "Actor.hpp"
#include <abyss/components/Actors/Commons/ActorTime.hpp>
#include <abyss/components/Actors/base/IUpdate.hpp>
#include <abyss/components/Actors/base/IMove.hpp>
#include <abyss/components/Actors/base/IPrePhysics.hpp>
#include <abyss/components/Actors/base/ILastPhysics.hpp>
#include <abyss/components/Actors/base/IPreCollision.hpp>
#include <abyss/components/Actors/base/ICollisionReact.hpp>
#include <abyss/components/Actors/base/ILastUpdate.hpp>
#include <abyss/components/Actors/base/IDraw.hpp>
#include <abyss/components/Actors/base/IPreDraw.hpp>

namespace abyss::Actor
{
	Actor::Actor()
	{
		m_time = this->attach<ActorTime>();
	}
	void Actor::updateDeltaTime(double worldDt) const
	{
		m_time->updateDeltaTime(worldDt);
	}
	void Actor::setup() const
	{
		m_components.setup();
	}
	void Actor::start()
	{
		m_components.start();
	}
	void Actor::update()
	{
		m_time->updateUpdateTime();
		for (auto&& com : this->finds<IUpdate>()) {
			com->onUpdate();
		}
	}
	void Actor::move()
	{
		for (auto&& com : this->finds<IMove>()) {
			com->onMove();
		}
	}
	void Actor::prePhysics()
	{
		for (auto&& com : this->finds<IPrePhysics>()) {
			com->onPrePhysics();
		}
	}
	void Actor::lastPhysics()
	{
		for (auto&& com : this->finds<ILastPhysics>()) {
			com->onLastPhysics();
		}
	}
	void Actor::preCollision()
	{
		for (auto&& com : this->finds<IPreCollision>()) {
			com->onPreCollision();
		}
	}

	void Actor::collisionReact()
	{
		for (auto&& com : this->finds<ICollisionReact>()) {
			com->onCollisionReact();
		}
	}

	void Actor::lastUpdate()
	{
		for (auto&& com : this->finds<ILastUpdate>()) {
			com->onLastUpdate();
		}
	}
	void Actor::draw() const
	{
		m_time->updateDrawTime();
		for (auto&& com : this->finds<IPreDraw>()) {
			com->onPreDraw();
		}
		for (auto&& com : this->finds<IDraw>()) {
			com->onDraw();
		}
	}
	s3d::Microseconds Actor::getUpdateTime() const
	{
		return m_time->getUpdateTime();
	}
	double Actor::getUpdateTimeSec() const
	{
		return m_time->getUpdateTimeSec();
	}
    std::function<s3d::Microseconds()> Actor::getUpdateTimer() const
    {
		return [this] {return this->getUpdateTime(); };
    }
	s3d::Microseconds Actor::getDrawTime() const
	{
		return m_time->getDrawTime();
	}
	double Actor::getDrawTimeSec() const
	{
		return m_time->getDrawTimeSec();
	}
	std::function<s3d::Microseconds()> Actor::getDrawTimer() const
	{
		return [this] {return this->getDrawTime(); };
	}
	double Actor::deltaTime() const
	{
		return m_time->getDeltaTime();
	}
}