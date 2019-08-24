#pragma once
#include "TimeUtil.hpp"
#include<Siv3D/Duration.hpp>

namespace abyss
{
	namespace Periodic{
		inline double Square0_1(double periodSec, double t = TimeUtil::Time())
		{
			return std::fmod(t, periodSec) < (periodSec * 0.5);
		}

		inline double Square0_1(const s3d::SecondsF& period, double t = TimeUtil::Time())
		{
			return Square0_1(static_cast<double>(period.count()), t);
		}

		inline double Sawtooth0_1(double periodSec, double t = TimeUtil::Time())
		{
			return std::fmod(t, periodSec) / periodSec;
		}

		inline double Sawtooth0_1(const s3d::SecondsF& period, double t = TimeUtil::Time())
		{
			return Sawtooth0_1(static_cast<double>(period.count()), t);
		}

		inline double Triangle0_1(double periodSec, double t = TimeUtil::Time())
		{
			const double x = std::fmod(t, periodSec) / (periodSec * 0.5);
			return x <= 1.0 ? x : 2.0 - x;
		}

		inline double Triangle0_1(const s3d::SecondsF& period, double t = TimeUtil::Time())
		{
			return Triangle0_1(static_cast<double>(period.count()), t);
		}
	}
}
