#include "ActorsHolder.hpp"

#include <Siv3D/Utility.hpp>

#include <abyss/modules/Actors/base/IActor.hpp>
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
				m_actors.push_back(std::move(obj));
			}
			m_actors.sort_by([](const std::shared_ptr<IActor>& a, const std::shared_ptr<IActor>& b) {
				return a->getOrder() < b->getOrder();
			});
		}
	}
    void ActorsHolder::pushActor(const std::shared_ptr<IActor>& obj)
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
		s3d::Erase_if(m_actors, [](const std::shared_ptr<IActor>& obj) {
			if (obj->isDestroyed()) {
				obj->end();
				return true;
			}
			return false;
		});
	}
	void ActorsHolder::onCheckIn()
	{
		s3d::Erase_if(m_reserves, [](const std::shared_ptr<IActor>& obj) {
			return obj->isDestoryCheckIn();
		});
		s3d::Erase_if(m_actors, [](const std::shared_ptr<IActor>& obj) {
			if (obj->isDestoryCheckIn()) {
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
	void ActorsHolder::onCheckOut()
	{
		s3d::Erase_if(m_reserves, [](const std::shared_ptr<IActor>& obj) {
			return obj->isDestoryCheckOut();
		});
		s3d::Erase_if(m_actors, [](const std::shared_ptr<IActor>& obj) {
			if (obj->isDestoryCheckOut()) {
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
	void ActorsHolder::clear()
	{
		for (auto&& actor : m_actors) {
			actor->end();
		}
		m_reserves.clear();
		m_actors.clear();

		m_objIdCounter = 0;
	}
	s3d::Array<std::shared_ptr<IActor>>& ActorsHolder::getActors()
	{
		return m_actors;
	}
	const s3d::Array<std::shared_ptr<IActor>>& ActorsHolder::getActors() const
	{
		return m_actors;
	}
}