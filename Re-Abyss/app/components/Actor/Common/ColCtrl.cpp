#include "ColCtrl.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/ColSys/CollisionManager.hpp>

namespace
{
	constexpr s3d::uint8 ActiveSlot = 1;
}
namespace abyss::Actor
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
		// 実際に登録するのはonStartのタイミング
		for (auto&& branch : m_branchs) {
			m_pActor->getModule<CollisionManager>()->regist(branch);
		}
	}
	void ColCtrl::onEnd()
	{
		for(auto&& branch : m_branchs) {
			if (branch) {
				branch->destroy();
			}
		}
	}
	ColCtrl& ColCtrl::setActive(bool isActive)
	{
		m_isActive = isActive;
		for (auto&& branch : m_branchs) {
			branch->setActive(m_isActive, ::ActiveSlot);
		}
		return *this;
	}
	Ref<ColSys::Branch> ColCtrl::addBranch()
	{
		auto ret = std::make_shared<ColSys::Branch>(m_id);
		ret->setActive(m_isActive, ::ActiveSlot);
		m_branchs << ret;
		return ret;
	}

	Ref<ColSys::Branch> ColCtrl::branch(size_t index) const
	{
		if (m_branchs.size() <= index) {
			return nullptr;
		}
		return m_branchs[index];
	}
	bool ColCtrl::isHitAny() const
	{
		return m_branchs.any([](const Ref<ColSys::Branch>& b) {
			return b && b->result().isHitAny();
		});
	}

	bool ColCtrl::isHitBy(std::type_index type) const
	{
		return m_branchs.any([type](const Ref<ColSys::Branch>& b) {
			return b && b->result().isHitBy(type);
		});
	}
}
