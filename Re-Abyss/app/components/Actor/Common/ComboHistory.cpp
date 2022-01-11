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
	bool ComboHistory::isDamaged(s3d::uint64 id) const
	{
		auto it = m_records.find(id);
		if (it == m_records.end()) {
			return true;
		}
		return it->second.invincibleTime <= 0;
	}
	s3d::int32 ComboHistory::getComboCount(s3d::uint64 id) const
	{
		auto it = m_records.find(id);
		if (it == m_records.end()) {
			return 0;
		}
		return it->second.comboCount;
	}
	void ComboHistory::updateRecord(s3d::uint64 id, double comboDuration, double invincibleTime)
	{
		auto& record = m_records[id];
		++record.comboCount;
		record.comboDuration = comboDuration;
		record.invincibleTime = invincibleTime;
	}
}
