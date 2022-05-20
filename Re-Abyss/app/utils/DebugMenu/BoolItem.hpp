#pragma once
#include <functional>
#include <abyss/utils/DebugMenu/INode.hpp>
#include <abyss/utils/DebugMenu/IItem.hpp>
#include <abyss/utils/DebugMenu/IValue.hpp>
#include <abyss/utils/DebugMenu/IFindable.hpp>
#include <Siv3D/String.hpp>

namespace abyss::DebugMenu
{
	class BoolItem :
		public INode,
		public IItem,
		public IValue,
		public IFindable
	{
	public:
		BoolItem() = default;
		BoolItem(
			const s3d::String& key,
			const s3d::String& label,
			bool initValue = false,
			const std::function<void(bool)>& callback = nullptr
		);

		void setCallback(const std::function<void(bool)>& callback)
		{
			m_callback = callback;
		}
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

		NodeValue value() const
		{
			return { m_value };
		}
	private:
		s3d::String m_key, m_label;
		bool m_value = false;
		std::function<void(bool)> m_callback;
	};
}