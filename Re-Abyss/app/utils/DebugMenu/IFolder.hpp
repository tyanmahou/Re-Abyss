#pragma once
#include <abyss/utils/DebugMenu/IItem.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::DebugMenu
{
	class IFolder
	{
	public:
		virtual ~IFolder() = default;

		virtual void onOpendUpdate() = 0;

		virtual bool isOpened() const = 0;
		virtual Ref<IItem> focusItem() const = 0;
		virtual s3d::Optional<size_t> focusIndex() const = 0;
	};
}