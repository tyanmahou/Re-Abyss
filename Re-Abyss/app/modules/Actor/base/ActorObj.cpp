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
		if (this->isActive()) {
			m_clock->updateTime();
		}
	}
	void ActorObj::preUpdate()
	{
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
		for (auto&& com : this->finds<IPreDraw>()) {
			com->onPreDraw();
		}
		auto drawer = this->getModule<DrawManager>();
		for (auto&& com : this->finds<IDraw>()) {
			drawer->add(com->getLayer(), [com] {
				com->onDraw();
			}, com->getOrder());
		}
	}
	s3d::Microseconds ActorObj::getTime() const
	{
		return m_clock->getTime();
	}
	double ActorObj::getTimeSec() const
	{
		return m_clock->getTimeSec();
	}
	s3d::ISteadyClock* ActorObj::getClock() const
    {
		return m_clock->getClock();
    }
	double ActorObj::deltaTime() const
	{
		return m_clock->getDeltaTime();
	}
}