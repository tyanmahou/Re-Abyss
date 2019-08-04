#include "TimeUtil.hpp"
#include <Siv3D/String.hpp>
#include <Siv3D/Duration.hpp>

namespace abyss
{
	void TimeUtil::updateTime()
	{
		s3d::uint64 prevTime = m_currentTime;
		m_currentTime = s3d::Time::GetNanosec();
		m_delta = static_cast<double>(m_currentTime - prevTime) / 1'000'000'000.0;
	}
	TimeUtil::TimeUtil()
	{
	}

	const s3d::String TimeUtil::name()
	{
		return L"TimeUtil";
	}

	s3d::String TimeUtil::getName() const
	{
		return name();
	}
	bool TimeUtil::init()
	{
		return true;
	}
	bool TimeUtil::update()
	{
		Instance()->updateTime();
		return true;
	}
	double TimeUtil::Delta()
	{
		return Instance()->m_delta;
	}
}