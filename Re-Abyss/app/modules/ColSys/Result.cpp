#include "Result.hpp"

namespace abyss::ColSys
{
	void Result::add(const HitData& hitData)
	{
		m_results.push_back(hitData);
	}

	void Result::onReflesh()
	{
		m_results.clear();
	}

	bool Result::isHitAny() const
	{
		return !m_results.empty();
	}

	bool Result::isHitBy(std::type_index type) const
	{
		return m_results.any([type](const HitData& hit) {
			return hit.extData.contains(type);
		});
	}
}
