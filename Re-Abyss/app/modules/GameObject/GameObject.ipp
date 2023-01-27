#pragma once

namespace abyss
{
	inline void GameObject::setManager(Manager* const pManager)
	{
		m_pManager = pManager;
	}
	inline Manager* GameObject::getManager() const
	{
		return m_pManager;
	}
	inline void GameObject::setActive(bool active)
	{
		m_isActive = active;
	}
	inline bool GameObject::isActive() const
	{
		return m_isActive;
	}
	inline void GameObject::destroy()
	{
		m_isDestroyed = true;
	}
	inline bool GameObject::isDestroyed() const
	{
		return m_isDestroyed;
	}

	template<class Module>
	Module* GameObject::getModule() const
	{
		if (!m_pManager) {
			return nullptr;
		}
		return m_pManager->getModule<Module>();
	}

	template<class Component>
	Ref<Component> GameObject::attach(const std::shared_ptr<Component>& component) const
		requires Componently<Component>
	{
		return m_components.add<Component>(component);
	}

	template<class Component, class... Args>
	Ref<Component> GameObject::attach(Args&&... args) const
		requires
		Componently<Component>&&
		std::constructible_from<Component, Args...>
	{
		return m_components.add<Component>(std::forward<Args>(args)...);
	}

	template<class Component>
	bool GameObject::detach() const
		requires Componently<Component>
	{
		return m_components.remove<Component>();
	}

	template<class Component>
	Ref<Component> GameObject::find() const
	{
		return m_components.find<Component>();
	}
	template<class Component>
	s3d::Array<Ref<Component>> GameObject::finds() const
	{
		return m_components.finds<Component>();
	}
	inline Ref<const GameObject> GameObject::getWeak() const
	{
		return shared_from_this();
	}
}
