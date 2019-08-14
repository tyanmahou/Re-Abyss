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

		// FIXME
		// Collision
		auto prevCollision = std::move(this->m_currentCollision);
		this->m_currentCollision.clear();

		for (auto it1 = m_objects.begin(); it1 != m_objects.end(); ++it1) {
			for (auto it2 = it1 + 1 ; it2 != m_objects.end(); ++it2) {
				if ((*it1)->getTag() == (*it2)->getTag()) {
					continue;
				}
				CollisionPairHash hash((*it1)->getId(), (*it2)->getId());
				if (abyss::Intersects((*it1)->getCollider(), (*it2)->getCollider())) {
					m_currentCollision.insert(hash);
					if (prevCollision.find(hash) != prevCollision.end()) {
						// onEnter
						(*it1)->onCollisionEnter(it2->get());
						(*it2)->onCollisionEnter(it1->get());
					}
					// onStay
					(*it1)->onCollisionStay(it2->get());
					(*it2)->onCollisionStay(it1->get());
				}
				else {
					if (prevCollision.find(hash) == prevCollision.end()) {
						// onExit
						(*it1)->onCollisionExit(it2->get());
						(*it2)->onCollisionExit(it1->get());
					}
				}
			}
		}

		// オブジェクトの削除
		Erase_if(m_objects, [](const std::shared_ptr<WorldObject> & obj) {
			return obj->isDelete();
		});
	}

	void WorldModel::draw() const
	{
		m_effect.update();
		for (const auto& obj : m_objects) {
			obj->draw();
		}
	}
	s3d::Effect& WorldModel::getEffect()
	{
		return m_effect;
	}
	void WorldModel::registerObject(const std::shared_ptr<WorldObject>& obj)
	{
		obj->setWorld(this);
		obj->setId(m_objIdCounter++);
		m_reserves.push_back(obj);
	}
	void WorldModel::registerObject(const std::shared_ptr<PlayerModel>& obj)
	{
		m_playerModel = obj.get();
		this->registerObject(static_cast<std::shared_ptr<WorldObject>>(obj));
	}
}