#pragma once
#include <functional>
#include <abyss/utils/DebugMenu/INode.hpp>
#include <abyss/utils/DebugMenu/IItem.hpp>
#include <abyss/utils/DebugMenu/IFindable.hpp>
#include <Siv3D/String.hpp>

namespace abyss::DebugMenu
{
	class Button :
		public INode,
		public IItem,
		public IFindable
	{
	public:
		Button() = default;
		Button(
			const s3d::String& key,
			const std::function<void()>& callback = nullptr
		);
		Button(
			const s3d::String& key,
			const s3d::String& label,
			const std::function<void()>& callback = nullptr
		);

	public:
		s3d::StringView key() const override
		{
			return m_key;
		}
	public:
		s3d::StringView label() const override
		{
			return m_label;
		}

		void onFoucsUpdate() override;

	private:
		s3d::String m_key, m_label;
		std::function<void()> m_callback;
	};
}