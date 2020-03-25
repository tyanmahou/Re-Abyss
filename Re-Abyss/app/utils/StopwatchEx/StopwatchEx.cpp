#include "StopwatchEx.hpp"
#include <Siv3D/String.hpp>

namespace abyss
{
	using namespace s3d;
	String StopwatchEx::format(const StringView format) const
	{
		return FormatTime(elapsed(), format);
	}


	bool operator <(const StopwatchEx& s, const MicrosecondsF& time)
	{
		return s.elapsed() < time;
	}

	bool operator <=(const StopwatchEx& s, const MicrosecondsF& time)
	{
		return s.elapsed() <= time;
	}

	bool operator >(const StopwatchEx& s, const MicrosecondsF& time)
	{
		return s.elapsed() > time;
	}

	bool operator >=(const StopwatchEx& s, const MicrosecondsF& time)
	{
		return s.elapsed() >= time;
	}


	bool operator <(const MicrosecondsF& time, const StopwatchEx& s)
	{
		return time < s.elapsed();
	}

	bool operator <=(const MicrosecondsF& time, const StopwatchEx& s)
	{
		return time <= s.elapsed();
	}

	bool operator >(const MicrosecondsF& time, const StopwatchEx& s)
	{
		return time > s.elapsed();
	}

	bool operator >=(const MicrosecondsF& time, const StopwatchEx& s)
	{
		return time >= s.elapsed();
	}
}
namespace s3d
{
	void Formatter(FormatData& formatData, const abyss::StopwatchEx& value)
	{
		formatData.string.append(value.format());
	}
}