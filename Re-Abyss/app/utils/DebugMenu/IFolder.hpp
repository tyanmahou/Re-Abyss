#pragma once
#include <abyss/utils/DebugMenu/IItem.hpp>
#include <abyss/utils/DebugMenu/INode.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <Siv3D/Optional.hpp>

namespace abyss::DebugMenu
{
	class IFolder : public IItem
	{
	public:
		virtual void onOpendUpdate(const IInputController* input) = 0;

		virtual bool isOpened() const = 0;
		virtual Ref<IItem> focusItem() const = 0;
		virtual s3d::Optional<size_t> focusIndex() const = 0;
		virtual const s3d::Array<std::shared_ptr<INode>>& childNodes() const = 0;
	};
}
