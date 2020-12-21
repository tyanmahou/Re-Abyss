#include "IActor.hpp"
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
	IActor::IActor()
	{
		m_time = this->attach<ActorTime>();
	}
	void IActor::updateDeltaTime(double worldDt) const
	{
		m_time->updateDeltaTime(worldDt);
	}
	void IActor::update()
	{
		m_time->updateUpdateTime();
		for (auto&& com : this->finds<IUpdate>()) {
			com->onUpdate();
		}
	}
	void IActor::move()
	{
		for (auto&& com : this->finds<IMove>()) {
			com->onMove();
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
	void IActor::preCollision()
	{
		for (auto&& com : this->finds<IPreCollision>()) {
			com->onPreCollision();
		}
	}

	void IActor::collisionReact()
	{
		for (auto&& com : this->finds<ICollisionReact>()) {
			com->onCollisionReact();
		}
	}

	void IActor::lastUpdate()
	{
		for (auto&& com : this->finds<ILastUpdate>()) {
			com->onLastUpdate();
		}
	}
	void IActor::draw() const
	{
		m_time->updateDrawTime();
		for (auto&& com : this->finds<IPreDraw>()) {
			com->onPreDraw();
		}
		for (auto&& com : this->finds<IDraw>()) {
			com->onDraw();
		}
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
	double IActor::deltaTime() const
	{
		return m_time->getDeltaTime();
	}
}