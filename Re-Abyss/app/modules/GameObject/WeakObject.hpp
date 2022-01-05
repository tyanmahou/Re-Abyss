#pragma once
#include <abyss/modules/GameObject/GameObject.hpp>

namespace abyss
{
	/// <summary>
	/// ゲームオブジェクトの弱参照
	/// </summary>
	class WeakObject
	{
	public:
		WeakObject() = default;

		WeakObject(GameObject* gameObject):
			m_handle(gameObject ? gameObject->getHandle() : nullptr)
		{}

		[[nodiscard]] explicit operator bool()const noexcept
		{
			return this->isValid();
		}
		[[nodiscard]] bool isValid() const
		{
			return static_cast<bool>(m_handle);
		}
	private:
		Ref<GameObject::Handle> m_handle;
	};
}