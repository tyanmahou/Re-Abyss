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

		WeakObject(GameObject* pGameObject):
			m_pGameObject(pGameObject ? pGameObject->getWeak() : nullptr)
		{}

		/// <summary>
		/// boolキャスト
		/// 有効状態ならtrue
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] explicit operator bool()const noexcept
		{
			return this->isValid();
		}

		/// <summary>
		/// 有効か
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] bool isValid() const
		{
			return static_cast<bool>(m_pGameObject);
		}

		/// <summary>
		/// コンポーネントを取得
		/// </summary>
		/// <typeparam name="Component"></typeparam>
		/// <returns></returns>
		template<class Component>
		[[nodiscard]] Ref<Component> find() const
		{
			if (!this->isValid()) {
				return nullptr;
			}
			return m_pGameObject->find<Component>();
		}
	private:
		Ref<const GameObject> m_pGameObject;
	};
}