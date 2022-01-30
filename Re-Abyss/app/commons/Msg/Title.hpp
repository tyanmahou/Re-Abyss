#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Msg
{
	struct Title
	{
		[[TOML_BIND(GameStart)]]
		inline static s3d::String GameStart;

		[[TOML_BIND(Exit)]]
		inline static s3d::String Exit;
	};
}