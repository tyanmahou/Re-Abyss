#pragma once
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GameObject/Components.hpp>
#include <Siv3D/Uncopyable.hpp>

namespace abyss
{
	class GameObject : 
		public std::enable_shared_from_this<GameObject>,
		s3d::Uncopyable
	{
	private:
		Components m_components;
		bool m_isActive = true;
		bool m_isDestroyed = false;

		Manager* m_pManager = nullptr;
	public:
		virtual ~GameObject() = default;

        bool isSetuped() const
        {
            return m_components.isSetuped();
        }
		void setup() const
		{
			m_components.setup();
		}
		void start() const
		{
			m_components.start();
		}
		void end() const
		{
			m_components.end();
		}

		void setManager(Manager* const pManager);
		Manager* getManager() const;

		void setActive(bool active);
		bool isActive() const;

		void destroy();
		bool isDestroyed() const;

		/// <summary>
		/// モジュールを取得
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		template<class Module>
		Module* getModule() const;

		/// <summary>
		/// コンポーネントを付与
		/// </summary>
		template<class Component>
		Ref<Component> attach(const std::shared_ptr<Component>& component) const
			requires IsComponent<Component>
			;

		/// <summary>
		/// コンポーネントを構築して付与
		/// </summary>
		template<class Component, class... Args>
		Ref<Component> attach(Args&&... args) const
			requires
			IsComponent<Component>&&
			std::constructible_from<Component, Args...>
			;

		/// <summary>
		/// コンポーネントを取り除きます
		/// </summary>
		template<class Component>
		bool detach() const
			requires IsComponent<Component>
			;

		/// <summary>
		/// コンポーネントを取得
		/// </summary>
		/// <typeparam name="Component"></typeparam>
		/// <returns></returns>
		template<class Component>
		[[nodiscard]] Ref<Component> find() const;

		/// <summary>
		/// コンポーネントを取得
		/// </summary>
		/// <typeparam name="Component"></typeparam>
		/// <returns></returns>
		template<class Component>
		[[nodiscard]] s3d::Array<Ref<Component>> finds() const;

		/// <summary>
		/// 弱参照取得
		/// </summary>
		/// <returns></returns>
		[[nodiscard]] Ref<const GameObject> getWeak() const;
	};
}
#include <abyss/modules/GameObject/GameObject.ipp>
