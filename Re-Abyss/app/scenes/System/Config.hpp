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
		static consteval Config SaveSelect()
		{
			return Config{
				.isStage = false
			};
		}
		static consteval Config Stage()
		{
			return Config{
				.isStage = true
			};
		}
        static consteval Config StageResult()
        {
            return Config{
                .isStage = false
            };
        }
    public:
		bool isStage = false;
	};
}
