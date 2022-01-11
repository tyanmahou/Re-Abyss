#include "ComboHistory.hpp"

namespace abyss::Actor
{
	void ComboHistory::update(double dt)
	{
		for (auto it = m_records.begin(); it != m_records.end(); ) {
			it->second.comboDuration -= dt;
			it->second.invincibleTime -= dt;
			if (it->second.comboDuration <= 0) {
				it = m_records.erase(it);
			} else {
				++it;
			}
		}
	}
	const ComboRecord& ComboHistory::find(s3d::uint64 id)
	{
		return m_records[id];
	}
	void ComboHistory::updateRecord(s3d::uint64 id, double comboDuration, double invincibleTime)
	{
		auto& record = m_records[id];
		++record.comboCount;
		record.comboDuration = comboDuration;
		record.invincibleTime = invincibleTime;
	}
}
