#pragma once

namespace abyss::Sys
{
	struct Config
	{
#if ABYSS_DEVELOP
        static consteval Config DevPortal()
        {
            return Config{
                .isStage = false,
                .useGitHub = true
            };
        }
#endif
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
        static consteval Config Home()
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

#if ABYSS_DEVELOP
        bool useGitHub = false;
#endif
	};
}
