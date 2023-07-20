#pragma once
#include <abyss/utils/DebugMenu/Folder.hpp>

namespace abyss::DebugMenu
{
	class RootFolder : public Folder
	{
	public:
		using Folder::Folder;
	public:
		void onOpendUpdate(const IInputController* input) override
		{
			Folder::onOpendUpdate(input);
		}
		bool isOpened() const override
		{
			return true;
		}
	};
}
