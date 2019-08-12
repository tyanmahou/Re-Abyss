#include "WorldModel.hpp"
#include "Collision.hpp"
#include "objects/PlayerModel.hpp"

#include "../util/TimeUtil.hpp"

#include <Siv3D.hpp>

namespace abyss
{
	void WorldModel::update()
	{
		double dt = TimeUtil::Delta();

		for (auto& obj : m_reserves) {
			m_objects.push_back(std::move(obj));
		}
		m_reserves.clear();

		for (auto& obj : m_objects) {
			obj->update(dt);
		}

		// オブジェクトの削除
		Erase_if(m_objects, [](const std::shared_ptr<WorldObject> & obj) {
			return obj->isDelete();
		});

		// FIXME
		// Collision
		for (auto it1 = m_objects.begin(); it1 != m_objects.end(); ++it1) {
			for (auto it2 = it1 + 1 ; it2 != m_objects.end(); ++it2) {
				if (abyss::Intersects((*it1)->getCollider(), (*it2)->getCollider())) {
					(*it1)->onCollisionStay(it2->get());
					(*it2)->onCollisionStay(it1->get());
				}
			}
		}
	}

	void WorldModel::draw() const
	{
		for (const auto& obj : m_objects) {
			obj->draw();
		}
	}
	void WorldModel::registerObject(const std::shared_ptr<WorldObject>& obj)
	{
		obj->setWorld(this);
		m_reserves.push_back(obj);
	}
	void WorldModel::registerObject(const std::shared_ptr<PlayerModel>& obj)
	{
		m_playerModel = obj.get();
		obj->setWorld(this);
		m_reserves.push_back(obj);
	}
}