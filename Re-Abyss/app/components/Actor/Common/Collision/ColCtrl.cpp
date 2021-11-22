#include "ColCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Collision/CollisionManager.hpp>

namespace abyss::Actor::Collision
{
	ColCtrl::ColCtrl(ActorObj* pActor):
		m_pActor(pActor),
		m_id(pActor->getModule<CollisionManager>()->createId())
	{}

	void ColCtrl::setup(Executer executer)
	{
	}
	void ColCtrl::onStart()
	{
	}
	void ColCtrl::onEnd()
	{
		for(auto&& branch : m_branchs) {
			if (branch) {
				branch->destroy();
			}
		}
	}

	Ref<abyss::Collision::Branch> ColCtrl::addBranch()
	{
		auto ret = m_pActor->getModule<CollisionManager>()->add(m_id);
		m_branchs << ret;
		return ret;
	}

	Ref<abyss::Collision::Branch> ColCtrl::branch(size_t index) const
	{
		if (m_branchs.size() <= index) {
			return nullptr;
		}
		return m_branchs[index];
	}
	bool ColCtrl::isHitAny() const
	{
		return m_branchs.any([](const Ref<abyss::Collision::Branch>& b) {
			return b && b->result().isHitAny();
		});
	}

	bool ColCtrl::isHitBy(std::type_index type) const
	{
		return m_branchs.any([type](const Ref<abyss::Collision::Branch>& b) {
			return b && b->result().isHitBy(type);
		});
	}
}
