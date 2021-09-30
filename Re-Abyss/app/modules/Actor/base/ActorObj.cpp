#include "ActorObj.hpp"
#include <abyss/components/Common/ClockCtrl.hpp>
#include <abyss/components/Actor/base/IPreUpdate.hpp>
#include <abyss/components/Actor/base/IUpdate.hpp>
#include <abyss/components/Actor/base/IPostUpdate.hpp>
#include <abyss/components/Actor/base/IMove.hpp>
#include <abyss/components/Actor/base/IPrePhysics.hpp>
#include <abyss/components/Actor/base/IPostPhysics.hpp>
#include <abyss/components/Actor/base/IPreCollision.hpp>
#include <abyss/components/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/base/IDraw.hpp>
#include <abyss/components/Actor/base/IPreDraw.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>

namespace abyss::Actor
{
	ActorObj::ActorObj()
	{
		m_clock = this->attach<ClockCtrl>(this);
	}
	void ActorObj::updateDeltaTime(double worldDt) const
	{
		m_clock->updateDeltaTime(worldDt);
	}
	void ActorObj::preUpdate()
	{
		m_clock->updateUpdateTime();
		for (auto&& com : this->finds<IPreUpdate>()) {
			com->onPreUpdate();
		}
	}
	void ActorObj::update()
	{
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
		auto drawer = this->getModule<DrawManager>();
		for (auto&& com : this->finds<IDraw>()) {
			drawer->add(com->getLayer(), [com] {
				com->onDraw();
			});
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
	s3d::ISteadyClock* ActorObj::getUpdateClock() const
    {
		return m_clock->getUpdateClock();
    }
	s3d::Microseconds ActorObj::getDrawTime() const
	{
		return m_clock->getDrawTime();
	}
	double ActorObj::getDrawTimeSec() const
	{
		return m_clock->getDrawTimeSec();
	}
	s3d::ISteadyClock* ActorObj::getDrawClock() const
	{
		return m_clock->getDrawClock();
	}
	double ActorObj::deltaTime() const
	{
		return m_clock->getDeltaTime();
	}
}