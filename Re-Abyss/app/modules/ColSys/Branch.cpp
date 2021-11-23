#include "Branch.hpp"
#include <abyss/utils/Collision/CollisionUtil.hpp>

namespace abyss::ColSys
{
	Branch::Branch(s3d::uint64 id):
		m_id(id)
	{
	}
	void Branch::onPreCollision()
	{
		m_result.onReflesh();
	}

	void Branch::onCollision(const Branch& other)
	{
		HitData data{};
		for (const auto& [type, extensino] : other.m_extensions) {
			data.extData.emplace(type, extensino->data());
		}
		m_result.add(std::move(data));
	}

	bool Branch::isCollision(const Branch& other) const
	{
		for (const auto& n1 : m_nodes) {
			for (const auto& n2 : other.m_nodes) {
				if (ColisionUtil::Intersects(n1->getShape(), n2->getShape())) {
					return true;
				}
			}
		}
		return false;
	}

	Branch& Branch::setActive(bool isActive, s3d::uint8 slot)
	{
		if (isActive) {
			m_isActiveBit |= (1 << slot);
		}
		else {
			m_isActiveBit &= ~(1 << slot);
		}
		return *this;
	}

	bool Branch::isActive() const
	{
		if (m_nodes.empty()) {
			return false;
		}
		if (m_isDestroyed) {
			return false;
		}
		return (m_isActiveBit & ActiveAll) == ActiveAll;
	}
	Branch& Branch::addNode(std::unique_ptr<INode>&& node)
	{
		m_nodes << std::move(node);
		return *this;
	}
	Branch& Branch::attach(std::type_index type, std::unique_ptr<IExtension>&& extension)
	{
		m_extensions.emplace(type, std::move(extension));
		return *this;
	}
}
