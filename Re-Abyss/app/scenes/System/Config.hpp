#pragma once

namespace abyss::Sys
{
	struct Config
	{
#if ABYSS_DEVELOP
        static consteval Config DevPortal()
        {
            return Config{
                .useProject = true
            };
        }
#endif
		static consteval Config Splash()
		{
			return Config{
			};
		}
		static consteval Config Title()
		{
			return Config{
			};
		}
		static consteval Config SaveSelect()
		{
			return Config{
			};
		}
        static consteval Config Home()
        {
            return Config{
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
            };
        }
    public:
		bool isStage = false;

#if ABYSS_DEVELOP
        bool useProject = false;
#endif
	};
}
