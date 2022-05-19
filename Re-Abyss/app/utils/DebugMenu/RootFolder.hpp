#pragma once
#include <abyss/utils/DebugMenu/Folder.hpp>

namespace abyss::DebugMenu
{
	class RootFolder : public Folder
	{
	public:
		using Folder::Folder;
	public:
		void onOpendUpdate() override
		{
			Folder::onOpendUpdate();
		}
		bool isOpened() const override
		{
			return true;
		}
	};
}