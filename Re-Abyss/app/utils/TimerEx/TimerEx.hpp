# pragma once
# include "../StopwatchEx/StopwatchEx.hpp"

namespace abyss
{
	/// <summary>
	/// タイマー
	/// </summary>
	class TimerEx
	{
	private:

		s3d::int64 m_initialTimeMicrosec = 0;

		s3d::int64 m_startTimeMicrosec = 0;

		s3d::int64 m_accumulationMicrosec = 0;

		bool m_isStarted = false;

		bool m_pausing = true;

		TimeGetFunction_t m_timeGetter;
	public:

		/// <summary>
		/// タイマーを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit TimerEx(double timeSec = 0.0, bool startImmediately = false, TimeGetFunction_t timeGetter = Time::GetNow);

		/// <summary>
		/// タイマーを作成します。
		/// </summary>
		/// <param name="startImmediately">
		/// 即座に計測を開始する場合は true
		/// </param>
		explicit TimerEx(const s3d::Duration& time, bool startImmediately = false, TimeGetFunction_t timeGetter = Time::GetNow);

		/// <summary>
		/// タイマーを開始・再開します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void start();

		/// <summary>
		/// タイマーの残り時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[日]
		/// </returns>
		[[nodiscard]] s3d::int32 d() const { return static_cast<s3d::int32>(d64()); }

		/// <summary>
		/// タイマーの残り時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[日]
		/// </returns>
		[[nodiscard]] s3d::int64 d64() const { return us() / (1000LL * 1000LL * 60LL * 60LL * 24LL); }

		/// <summary>
		/// タイマーの残り時間を[日]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[日]
		/// </returns>
		[[nodiscard]] double dF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL * 24LL)); }

		/// <summary>
		/// タイマーの残り時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[時]
		/// </returns>
		[[nodiscard]] s3d::int32 h() const { return static_cast<s3d::int32>(h64()); }

		/// <summary>
		/// タイマーの残り時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[時]
		/// </returns>
		[[nodiscard]] s3d::int64 h64() const { return us() / (1000LL * 1000LL * 60LL * 60LL); }

		/// <summary>
		/// タイマーの残り時間を[時]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[時]
		/// </returns>
		[[nodiscard]] double hF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL * 60LL)); }

		/// <summary>
		/// タイマーの残り時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[分]
		/// </returns>
		[[nodiscard]] s3d::int32 min() const { return static_cast<s3d::int32>(min64()); }

		/// <summary>
		/// タイマーの残り時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[分]
		/// </returns>
		[[nodiscard]] s3d::int64 min64() const { return us() / (1000LL * 1000LL * 60LL); }

		/// <summary>
		/// タイマーの残り時間を[分]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[分]
		/// </returns>
		[[nodiscard]] double minF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL * 60LL)); }

		/// <summary>
		/// タイマーの残り時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[秒]
		/// </returns>
		[[nodiscard]] s3d::int32 s() const { return static_cast<s3d::int32>(s64()); }

		/// <summary>
		/// タイマーの残り時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[秒]
		/// </returns>
		[[nodiscard]] s3d::int64 s64() const { return us() / (1000LL * 1000LL); }

		/// <summary>
		/// タイマーの残り時間を[秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[秒]
		/// </returns>
		[[nodiscard]] double sF() const { return static_cast<double>(us() / static_cast<double>(1000LL * 1000LL)); }

		/// <summary>
		/// タイマーの残り時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[ミリ秒]
		/// </returns>
		[[nodiscard]] s3d::int32 ms() const { return static_cast<s3d::int32>(ms64()); }

		/// <summary>
		/// タイマーの残り時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[ミリ秒]
		/// </returns>
		[[nodiscard]] s3d::int64 ms64() const { return us() / (1000LL); }

		/// <summary>
		/// タイマーの残り時間を[ミリ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[ミリ秒]
		/// </returns>
		[[nodiscard]] double msF() const { return static_cast<double>(us() / static_cast<double>(1000LL)); }

		/// <summary>
		/// タイマーの残り時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[マイクロ秒]
		/// </returns>
		[[nodiscard]] s3d::int64 us() const;

		/// <summary>
		/// タイマーの残り時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[マイクロ秒]
		/// </returns>
		[[nodiscard]] s3d::int64 us64() const
		{
			return us();
		}

		/// <summary>
		/// タイマーの残り時間を[マイクロ秒]で返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間[マイクロ秒]
		/// </returns>
		[[nodiscard]] double usF() const { return static_cast<double>(us()); }

		/// <summary>
		/// タイマーの初期設定時間を返します。
		/// </summary>
		/// <returns>
		/// タイマーの初期設定時間
		/// </returns>
		[[nodiscard]] s3d::Duration duration() const { return s3d::SecondsF(m_initialTimeMicrosec / static_cast<double>(1000LL * 1000LL)); }

		/// <summary>
		/// タイマーの残り時間を返します。
		/// </summary>
		/// <returns>
		/// タイマーの残り時間
		/// </returns>
		[[nodiscard]] s3d::Duration remaining() const { return s3d::SecondsF(sF()); }

		/// <summary>
		/// タイマーの進み具合を 1 から 0 の範囲で返します。
		/// </summary>
		/// <returns>
		/// タイマーの進み具合 (1.0 から始まり、0.0 で終わる)
		/// </returns>
		[[nodiscard]] double progress1_0() const
		{
			return static_cast<double>(us()) / m_initialTimeMicrosec;
		}

		/// <summary>
		/// タイマーの進み具合を 0 から 1 の範囲で返します。
		/// </summary>
		/// <returns>
		/// タイマーの進み具合 (0.0 から始まり、1.0 で終わる)
		/// </returns>
		[[nodiscard]] double progress0_1() const
		{
			return 1.0 - progress1_0();
		}

		/// <summary>
		/// タイマーが 0 に達しているかを返します。
		/// </summary>
		/// <returns>
		/// タイマーが 0 に達している場合は true, それ以外の場合は false
		/// </returns>
		[[nodiscard]] bool reachedZero() const
		{
			return us() <= 0;
		}

		/// <summary>
		/// タイマーが動作中であるかを示します。
		/// </summary>
		/// <remarks>
		/// タイマーが開始されている、または開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		[[nodiscard]] bool isStarted() const { return m_isStarted; }

		/// <summary>
		/// タイマーが一時停止中であるかを示します。
		/// </summary>
		/// <remarks>
		/// タイマーが開始後一時停止中である場合 true, それ以外の場合は false
		/// </remarks>
		[[nodiscard]] bool isPaused() const { return m_isStarted && m_pausing; }

		/// <summary>
		/// タイマーが時間を計測中であるかを示します。
		/// </summary>
		/// <remarks>
		/// タイマーが開始されていて、なおかつ一時停止中でない場合 true, それ以外の場合は false
		/// </remarks>
		[[nodiscard]] bool isRunning() const { return m_isStarted && !m_pausing; }

		/// <summary>
		/// タイマーを一時停止します。
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
		/// タイマーが一時停止中である場合、再開します。
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
		/// タイマーを最初の設定時刻から開始しなおします。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart();

		/// <summary>
		/// タイマーの残り時間を変更して、タイマーを開始します。
		/// </summary>
		/// <returns>
		/// なし
		/// </returns>
		void restart(const s3d::Duration& time);

		/// <summary>
		/// タイマーの残り時間を変更します。
		/// </summary>
		/// <param name="time">
		/// 新しく設定する残り時間
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
		/// フォーマットされた残り時間
		/// </returns>
		[[nodiscard]] s3d::String format(s3d::StringView format = U"H:mm:ss.xx"_sv) const;
	};


	[[nodiscard]] bool operator <(const TimerEx& timer, const s3d::MicrosecondsF& time);

	[[nodiscard]] bool operator <=(const TimerEx& timer, const s3d::MicrosecondsF& time);

	[[nodiscard]] bool operator >(const TimerEx& timer, const s3d::MicrosecondsF& time);

	[[nodiscard]] bool operator >=(const TimerEx& timer, const s3d::MicrosecondsF& time);


	[[nodiscard]] bool operator <(const s3d::MicrosecondsF& time, const TimerEx& timer);

	[[nodiscard]] bool operator <=(const s3d::MicrosecondsF& time, const TimerEx& timer);

	[[nodiscard]] bool operator >(const s3d::MicrosecondsF& time, const TimerEx& timer);

	[[nodiscard]] bool operator >=(const s3d::MicrosecondsF& time, const TimerEx& timer);
}

//////////////////////////////////////////////////
//
//	Format
//
//////////////////////////////////////////////////

namespace s3d
{
	void Formatter(FormatData& formatData, const abyss::TimerEx& value);

	template <class CharType>
	inline std::basic_ostream<CharType>& operator <<(std::basic_ostream<CharType> output, const abyss::TimerEx& value)
	{
		return output << value.format();
	}
}