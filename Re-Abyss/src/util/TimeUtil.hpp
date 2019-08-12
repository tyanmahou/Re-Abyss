#pragma once
#include <Siv3D/Addon.hpp>
#include <Siv3D/Time.hpp>

namespace abyss
{
	class TimeUtil : public s3d::IAddon
	{
		s3d::uint64 m_currentTime;
		double m_delta = 0;
		double m_time = 0;
		static TimeUtil* Instance()
		{
			static TimeUtil instance;
			return &instance;
		}

		void updateTime();
	public:
		TimeUtil();

		static const s3d::String name();

		s3d::String getName() const override;

		bool init() override;

		bool update() override;

		static double Delta();
		static double Time();
	};
}