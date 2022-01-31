#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <Siv3D/String.hpp>

namespace abyss::Msg
{
	struct SaveSelect
	{
		[[TOML_BIND(Mode)]]
		struct Mode
		{
			[[TOML_BIND(GameStart)]]
			inline static s3d::String GameStart;

			[[TOML_BIND(Delete)]]
			inline static s3d::String Delete;
		};
	private:
		[[no_unique_address]] Mode Mode;
	};
}