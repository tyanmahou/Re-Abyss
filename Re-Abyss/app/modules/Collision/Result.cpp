#include "Result.hpp"

namespace abyss::Collision
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
}
