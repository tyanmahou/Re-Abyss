#include "TimerEx.hpp"

namespace abyss
{
	using namespace s3d;
	TimerEx::TimerEx(const double timeSec, const bool startImmediately, Clock_t timeGetter)
		: m_initialTimeMicrosec(static_cast<int64>(timeSec * 1'000'000)),
		m_timeGetter(timeGetter)
	{
		set(SecondsF(timeSec));

		if (startImmediately) {
			start();
		}
	}

	TimerEx::TimerEx(const Duration& time, const bool startImmediately, Clock_t timeGetter)
		: m_initialTimeMicrosec(static_cast<int64>(time.count() * 1'000'000)),
		m_timeGetter(timeGetter)
	{
		set(time);

		if (startImmediately) {
			start();
		}
	}

	void TimerEx::start()
	{
		if (!m_pausing) {
			return;
		}

		m_isStarted = true;

		m_pausing = false;

		m_startTimeMicrosec = m_timeGetter().count();
	}

	int64 TimerEx::us() const
	{
		const int64 t = m_timeGetter().count();

		if (!m_isStarted) {
			return 0;
		}

		if (m_pausing) {
			return Max<int64>(m_accumulationMicrosec, 0);
		}

		return Max<int64>(m_accumulationMicrosec - (t - m_startTimeMicrosec), 0);
	}

	void TimerEx::restart()
	{
		set(MicrosecondsF(m_initialTimeMicrosec));

		start();
	}

	void TimerEx::restart(const Duration& time)
	{
		set(time);

		start();
	}

	String TimerEx::format(const StringView format) const
	{
		return StopwatchEx(remaining(), false, m_timeGetter).format(format);
	}

	bool operator <(const TimerEx& timer, const MicrosecondsF& time)
	{
		return timer.remaining() < time;
	}

	bool operator <=(const TimerEx& timer, const MicrosecondsF& time)
	{
		return timer.remaining() <= time;
	}

	bool operator >(const TimerEx& timer, const MicrosecondsF& time)
	{
		return timer.remaining() > time;
	}

	bool operator >=(const TimerEx& timer, const MicrosecondsF& time)
	{
		return timer.remaining() >= time;
	}


	bool operator <(const MicrosecondsF& time, const TimerEx& timer)
	{
		return time < timer.remaining();
	}

	bool operator <=(const MicrosecondsF& time, const TimerEx& timer)
	{
		return time <= timer.remaining();
	}

	bool operator >(const MicrosecondsF& time, const TimerEx& timer)
	{
		return time > timer.remaining();
	}

	bool operator >=(const MicrosecondsF& time, const TimerEx& timer)
	{
		return time >= timer.remaining();
	}
}
namespace s3d
{
	void Formatter(FormatData& formatData, const abyss::TimerEx& value)
	{
		formatData.string.append(value.format());
	}
}