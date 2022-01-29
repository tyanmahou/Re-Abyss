#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Msg
{
	struct Common
	{
		[[TOML_BIND(Decide)]]
		inline static s3d::String  Decide;

		[[TOML_BIND(Cancel)]]
		inline static s3d::String  Cancel;

		[[TOML_BIND(UserPlayMode)]]
		struct UserPlayMode
		{
			[[TOML_BIND(Normal)]]
			inline static s3d::String Normal{};
			[[TOML_BIND(Hard)]]
			inline static s3d::String Hard{};
		};
	private:
		[[no_unique_address]] UserPlayMode UserPlayMode;
	};
}