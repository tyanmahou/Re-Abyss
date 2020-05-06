#include "ActorsHolder.hpp"

#include <Siv3D/Utility.hpp>

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/debugs/DebugManager/DebugManager.hpp>

namespace abyss
{
    void ActorsHolder::flush()
    {
		if (!m_reserves.empty()) {
			// startでregistされてもいいようにここでmove
			auto registing = std::move(m_reserves);
			m_reserves.clear();
			for (auto& obj : registing) {
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
	void ActorsHolder::update(double dt)
	{
		this->flush();

		for (auto& obj : m_actors) {
			obj->update(dt);
		}
	}
	void ActorsHolder::lastUpdate(double dt)
	{
		for (auto& obj : m_actors) {
			obj->lastUpdate(dt);
		}
	}
	void ActorsHolder::draw() const
	{
		for (auto& obj : m_actors) {
			obj->draw();
#if ABYSS_DEBUG
			if (DebugManager::IsDrawColider()) {
				DebugManager::DrawColider(obj->getCollider());
			}
#endif
		}
	}
	void ActorsHolder::erase()
	{
		s3d::Erase_if(m_actors, [](const std::shared_ptr<IActor>& obj) {
			return obj->isDelete();
		});
	}
	void ActorsHolder::clear()
	{
		auto isDestroyOnLoad = [](const std::shared_ptr<IActor>& obj) {
			return !obj->isDontDestoryOnLoad();
		};
		s3d::Erase_if(m_reserves, isDestroyOnLoad);
		s3d::Erase_if(m_actors, isDestroyOnLoad);
		m_objIdCounter = 0;

		for (auto& actor : m_actors) {
			actor->setId(m_objIdCounter++);
		}
		for (auto& actor : m_reserves) {
			actor->setId(m_objIdCounter++);
		}

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