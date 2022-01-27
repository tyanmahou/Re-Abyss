#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Msg
{
	struct Common
	{
		[[TOML_BIND(UserPlayMode::Normal)]]
		[[TOML_BIND(UserPlayMode::Hard)]]
		struct UserPlayMode
		{
			inline static s3d::String Normal{};
			inline static s3d::String Hard{};
		};
	};
}