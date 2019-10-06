#include "WorldModel.hpp"
#include <domain/actor/IActor.hpp>

#include <Siv3D/Utility.hpp>
#include <Siv3D/Scene.hpp>

namespace abyss
{
	void WorldModel::pushActor(const std::shared_ptr<IActor>& obj)
	{
		obj->setId(m_objIdCounter++);
		m_reserves.push_back(obj);
	}
	void WorldModel::update()
	{
		double dt = s3d::Scene::DeltaTime();

		if (!m_reserves.empty()) {
			for (auto& obj : m_reserves) {
				obj->start();
				m_actors.push_back(std::move(obj));
			}
			m_reserves.clear();
		}

		for (auto& obj : m_actors) {
			obj->update(dt);
		}
	}
	void WorldModel::draw() const
	{
		for (auto& obj : m_actors) {
			obj->draw();
		}
	}
	void WorldModel::erase()
	{
		s3d::Erase_if(m_actors, [](const std::shared_ptr<IActor>& obj) {
			return obj->isDelete();
		});
	}
	void WorldModel::clear()
	{
		m_reserves.clear();
		m_actors.clear();
		m_objIdCounter = 0;
	}
	s3d::Array<std::shared_ptr<IActor>>& WorldModel::getActors()
	{
		return m_actors;
	}
	const s3d::Array<std::shared_ptr<IActor>>& WorldModel::getActors() const
	{
		return m_actors;
	}
}
