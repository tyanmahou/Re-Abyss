#pragma once
#include <abyss/utils/TOML/TOMLBind.hpp>
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

		[[TOML_BIND(CreateUser)]]
		struct CreateUser
		{
			[[TOML_BIND(Title)]]
			inline static s3d::String Title;
		};

		[[TOML_BIND(EraseUser)]]
		struct EraseUser
		{
			[[TOML_BIND(Title)]]
			inline static s3d::String Title;
		};
	private:
		[[no_unique_address]] Mode Mode;
		[[no_unique_address]] CreateUser CreateUser;
		[[no_unique_address]] EraseUser EraseUser;
	};
}