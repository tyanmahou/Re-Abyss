#pragma once
#include <Siv3D/StringView.hpp>
#include <abyss/utils/DebugMenu/IInputController.hpp>

namespace abyss::DebugMenu
{
	class IItem
	{
	public:
        virtual ~IItem() = default;

		virtual s3d::StringView label() const = 0;

		virtual void onFoucsUpdate(const IInputController* input) = 0;
	};
}
