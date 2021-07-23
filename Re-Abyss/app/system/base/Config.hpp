#pragma once

namespace abyss::Sys
{
	struct Config
	{
		static consteval Config Splash()
		{
			return Config{
				.isStage = false
			};
		}
		static consteval Config Title()
		{
			return Config{
				.isStage = false
			};
		}
		static consteval Config Main()
		{
			return Config{
				.isStage = true
			};
		}
	public:
		bool isStage = false;
	};
}