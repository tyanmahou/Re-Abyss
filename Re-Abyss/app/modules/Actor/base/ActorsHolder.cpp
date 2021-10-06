#include "ActorsHolder.hpp"

#include <Siv3D/Utility.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
namespace abyss::Actor
{
    void ActorsHolder::flush()
    {
		if (!m_reserves.empty()) {
			// startでregistされてもいいようにここでmove
			auto registing = std::move(m_reserves);
			m_reserves.clear();
			for (auto& obj : registing) {
				obj->setup();
				obj->start();
				if (obj->isDestroyed()) {
					obj->end();
				} else {
					m_actors.push_back(std::move(obj));
				}
			}
		}
	}
    void ActorsHolder::pushActor(const std::shared_ptr<ActorObj>& obj)
	{
		obj->setId(m_objIdCounter++);
		m_reserves.push_back(obj);
	}
	void ActorsHolder::updateDeltaTime(double dt)
	{
		for (auto& obj : m_actors) {
			obj->updateDeltaTime(dt);
		}
	}
	void ActorsHolder::preUpdate()
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->preUpdate();
		}
	}
	void ActorsHolder::update()
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->update();
		}
	}
	void ActorsHolder::postUpdate()
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->postUpdate();
		}
	}
	void ActorsHolder::move() const
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->move();
		}
	}
	void ActorsHolder::prePhysics() const
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->prePhysics();
		}
	}
	void ActorsHolder::postPhysics() const
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->postPhysics();
		}
	}

	void ActorsHolder::preCollision() const
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->preCollision();
		}
	}

	void ActorsHolder::postCollision() const
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->postCollision();
		}
	}

	void ActorsHolder::lastUpdate()
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->lastUpdate();
		}
	}
	void ActorsHolder::draw() const
	{
		for (auto& obj : m_actors) {
			if (!obj->isActive()) {
				continue;
			}
			obj->draw();
		}
	}
	void ActorsHolder::erase()
	{
		s3d::Erase_if(m_actors, [](const std::shared_ptr<ActorObj>& obj) {
			if (obj->isDestroyed()) {
				obj->end();
				return true;
			}
			return false;
		});
	}
	void ActorsHolder::onCheckIn(BufferLayer layer)
	{
		this->clear(DestoryTiming::CheckIn, layer);
	}
	void ActorsHolder::onCheckOut(BufferLayer layer)
	{
		this->clear(DestoryTiming::CheckOut, layer);
	}
	void ActorsHolder::clear()
	{
		for (auto&& actor : m_actors) {
			actor->end();
		}
		m_reserves.clear();
		m_actors.clear();

		m_objIdCounter = 0;
	}
	void ActorsHolder::clear(DestoryTiming timing, BufferLayer layer)
	{
		s3d::Erase_if(m_reserves, [&](const std::shared_ptr<ActorObj>& obj) {
			return obj->getDestoryTiming() == timing && obj->getBufferLayer() == layer;
		});
		s3d::Erase_if(m_actors, [&](const std::shared_ptr<ActorObj>& obj) {
			if (obj->getDestoryTiming() == timing && obj->getBufferLayer() == layer) {
				obj->end();
				return true;
			}
			return false;
		});
		m_objIdCounter = 0;
		for (auto& actor : m_actors) {
			actor->setId(m_objIdCounter++);
		}
		for (auto& actor : m_reserves) {
			actor->setId(m_objIdCounter++);
		}
	}

	s3d::Array<std::shared_ptr<ActorObj>>& ActorsHolder::getActors()
	{
		return m_actors;
	}
	const s3d::Array<std::shared_ptr<ActorObj>>& ActorsHolder::getActors() const
	{
		return m_actors;
	}
}