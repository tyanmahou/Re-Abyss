#pragma once
#include <Siv3D/Fwd.hpp>
#include "../Clock/Clock.hpp"

namespace abyss
{
	using namespace s3d::Literals;

	/// <summary>
	/// カスタムストップウォッチ
	/// Stopwatch
	/// </summary>
	class StopwatchEx
	{

	private:

		s3d::int64 m_startTimeMicrosec = 0;

		s3d::int64 m_accumulationMicrosec = 0;

		bool m_isStarted = false;

		bool m_pausing = true;

		Clock_t m_timeGetter;
	public:

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit StopwatchEx(bool startImmediately = false, Clock_t timeGetter = Clock::GetNow):
			m_timeGetter(timeGetter)
		{
			if (startImmediately) {
				start();
			}
		}

		/// <summary>
		/// ストップウォッチを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit StopwatchEx(const s3d::Duration& time, bool startImmediately = false, Clock_t timeGetter = Clock::GetNow):
			m_timeGetter(timeGetter)
		{
			set(time);

			if (startImmediately) {
				start();
			}
		}

		/// <summary>
		/// デストラクタ
		/// </summary>
		virtual ~StopwatchEx() = default;

		/// <summary>
		/// ストップウォッチを開始・再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void start()
		{
			if (!m_pausing) {
				return;
			}

			m_isStarted = true;

			m_pausing = false;

			m_startTimeMicrosec = m_timeGetter().count();
		}

		/// <summary>
		/// ストップウォッチの経過時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[日]
		/// </returns>
		[[nodiscard]] s3d::int32 d() const { return static_cast<s3d::int32>(d64()); }

		[[nodiscard]] s3d::int64 d64() const { return us() / (1000LL * 1000LL * 60LL * 60LL * 24LL); }

		[[nodiscard]] double dF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL * 24LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[時]
		/// </returns>
		[[nodiscard]] s3d::int32 h() const { return static_cast<s3d::int32>(h64()); }

		[[nodiscard]] s3d::int64 h64() const { return us() / (1000LL * 1000LL * 60LL * 60LL); }

		[[nodiscard]] double hF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[分]
		/// </returns>
		[[nodiscard]] s3d::int32 min() const { return static_cast<s3d::int32>(min64()); }

		[[nodiscard]] s3d::int64 min64() const { return us() / (1000LL * 1000LL * 60LL); }

		[[nodiscard]] double minF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[秒]
		/// </returns>
		[[nodiscard]] s3d::int32 s() const { return static_cast<s3d::int32>(s64()); }

		[[nodiscard]] s3d::int64 s64() const { return us() / (1000LL * 1000LL); }

		[[nodiscard]] double sF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[ミリ秒]
		/// </returns>
		[[nodiscard]] s3d::int32 ms() const { return static_cast<s3d::int32>(ms64()); }

		[[nodiscard]] s3d::int64 ms64() const { return us() / (1000LL); }

		[[nodiscard]] double msF() const { return static_cast<double>(us() / static_cast<double>(1000LL)); }

		/// <summary>
		/// ストップウォッチの経過時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間[マイクロ秒]
		/// </returns>
		[[nodiscard]] s3d::int64 us() const
		{
			const s3d::int64 t = m_timeGetter().count();

			if (!m_isStarted) {
				return 0;
			}

			if (m_pausing) {
				return m_accumulationMicrosec;
			}

			return m_accumulationMicrosec + (t - m_startTimeMicrosec);
		}

		[[nodiscard]] s3d::int64 us64() const
		{
			return us();
		}

		[[nodiscard]] double usF() const { return static_cast<double>(us()); }

		/// <summary>
		/// ストップウォッチの経過時間を返します。
		/// </summary>
		/// <returns>
		/// ストップウォッチの経過時間
		/// </returns>
		[[nodiscard]] s3d::Duration elapsed() const { return s3d::SecondsF(sF()); }

		/// <summary>
		/// ストップウォッチが動作中であるかを示します（一時停止していることもあります）。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		[[nodiscard]] bool isStarted() const { return m_isStarted; }

		/// <summary>
		/// ストップウォッチが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		[[nodiscard]] bool isPaused() const { return m_isStarted && m_pausing; }

		/// <summary>
		/// ストップウォッチが時間を計測中であるかを示します。
		/// </summary>
		/// <remarks>
		/// ストップウォッチが開始されていて、なおかつ一時停止中でない場合 true, それ以外の場合は false
		/// </remarks>
		[[nodiscard]] bool isRunning() const { return m_isStarted && !m_pausing; }

		/// <summary>
		/// ストップウォッチを一時停止します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void pause()
		{
			m_accumulationMicrosec = us();

			m_pausing = true;
		}

		/// <summary>
		/// ストップウォッチが一時停止中である場合、再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void resume()
		{
			if (!isPaused()) {
				return;
			}

			start();
		}

		/// <summary>
		/// ストップウォッチを停止し、経過時間を 0 にリセットします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void reset() noexcept
		{
			m_accumulationMicrosec = 0;

			m_isStarted = false;

			m_pausing = true;
		}

		/// <summary>
		/// 経過時間を 0 にリセットして、ストップウォッチを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart()
		{
			reset();

			start();
		}

		/// <summary>
		/// ストップウォッチの経過時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する経過時間
		/// </param>
		/// <returns>
		/// なし
		/// </returns>
		void set(const s3d::Duration& time)
		{
			m_isStarted = true;

			m_accumulationMicrosec = static_cast<s3d::int64>(time.count() * (1000LL * 1000LL));

			m_startTimeMicrosec = m_timeGetter().count();
		}

		/// <summary>
		/// DD		日 (00-)
		/// D		日 (0-)
		/// dd		日 (00-)
		/// d		日 (0-)
		/// HH		時 (00-)
		/// H		時 (0-)
		/// hh		時 (00-24)
		/// h		時 (0-24)
		/// MM		分 (00-)
		/// M		分 (0-)
		/// mm		分 (00-59)
		/// m		分 (0-59)
		/// SS		秒 (00-)
		/// S		秒 (0-)
		/// ss		秒 (00-59)
		/// s		秒 (0-59)
		/// X		ミリ秒 (0-)
		/// x		小数点以下 1 桁秒 (0-9)
		/// xx		小数点以下 2 桁秒 (00-99)
		/// xxx		小数点以下 3 桁秒 (000-999)
		/// </summary>
		/// <param name="format">
		/// フォーマット指定
		/// </param>
		/// <returns>
		/// フォーマットされた経過時間
		/// </returns>
		[[nodiscard]] s3d::String format(s3d::StringView format = U"H:mm:ss.xx"_sv) const;
	};

	[[nodiscard]] bool operator <(const StopwatchEx& s, const s3d::MicrosecondsF& time);

	[[nodiscard]] bool operator <=(const StopwatchEx& s, const s3d::MicrosecondsF& time);

	[[nodiscard]] bool operator >(const StopwatchEx& s, const s3d::MicrosecondsF& time);

	[[nodiscard]] bool operator >=(const StopwatchEx& s, const s3d::MicrosecondsF& time);


	[[nodiscard]] bool operator <(const s3d::MicrosecondsF& time, const StopwatchEx& s);

	[[nodiscard]] bool operator <=(const s3d::MicrosecondsF& time, const StopwatchEx& s);

	[[nodiscard]] bool operator >(const s3d::MicrosecondsF& time, const StopwatchEx& s);

	[[nodiscard]] bool operator >=(const s3d::MicrosecondsF& time, const StopwatchEx& s);
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const abyss::StopwatchEx& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType> output, const abyss::StopwatchEx& value)
	{
		return output << value.format();
	}
}