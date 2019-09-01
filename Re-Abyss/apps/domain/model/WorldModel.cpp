#include "WorldModel.hpp"
#include <application/util/TimeUtil.hpp>
#include <domain/model/object/WorldObject.hpp>

#include <Siv3D/Utility.hpp>
namespace abyss
{
	void WorldModel::pushObject(const std::shared_ptr<WorldObject>& obj)
	{
		obj->setId(m_objIdCounter++);
		m_reserves.push_back(obj);
	}
	void WorldModel::update()
	{
		double dt = TimeUtil::Delta();

		if (!m_reserves.empty()) {
			for (auto& obj : m_reserves) {
				obj->start();
				m_objects.push_back(std::move(obj));
			}
			m_reserves.clear();
		}

		for (auto& obj : m_objects) {
			obj->update(dt);
		}
	}
	void WorldModel::draw() const
	{
		for (auto& obj : m_objects) {
			obj->draw();
		}
	}
	void WorldModel::erase()
	{
		s3d::Erase_if(m_objects, [](const std::shared_ptr<WorldObject>& obj) {
			return obj->isDelete();
		});
	}
	void WorldModel::clear()
	{
		m_reserves.clear();
		m_objects.clear();
		m_objIdCounter = 0;
	}
	s3d::Array<std::shared_ptr<WorldObject>>& WorldModel::getObjects()
	{
		return m_objects;
	}
	const s3d::Array<std::shared_ptr<WorldObject>>& WorldModel::getObjects() const
	{
		return m_objects;
	}
}
