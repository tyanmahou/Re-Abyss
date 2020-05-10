#pragma once

namespace abyss
{
	inline void IActor::setManager(ActManager* const pManager)
	{
		m_pManager = pManager;
	}
	inline ActManager* IActor::getManager() const
	{
		return m_pManager;
	}
	inline void IActor::setId(s3d::uint64 id)
	{
		m_id = id;
	}

	inline s3d::uint64 IActor::getId() const
	{
		return m_id;
	}

	inline void IActor::setActive(bool active)
	{
		m_isActive = active;
	}
	inline bool IActor::isActive() const
	{
		return m_isActive;
	}
	inline void IActor::destroy()
	{
		m_isDestroyed = true;
	}
	inline bool IActor::isDestroyed() const
	{
		return m_isDestroyed;
	}
	inline bool IActor::isDontDestoryOnLoad() const
	{
		return m_isDontDestoryOnLoad;
	}
	inline s3d::int32 IActor::getOrder() const
	{
		return m_order;
	}

	template<class T>
	T* IActor::getModule() const
	{
		if (!m_pManager) {
			return nullptr;
		}
		return m_pManager->getModule<T>();
	}

	template<class Component>
	Ref<Component> IActor::attach(const std::shared_ptr<Component>& component)
		requires IsComponent<Component>
	{
		return m_components.add<Component>(component);
	}

	template<class Component, class... Args>
	Ref<Component> IActor::attach(Args&&... args)
		requires
		IsComponent<Component>&&
		std::constructible_from<Component, Args...>
	{
		return m_components.add<Component>(std::forward<Args>(args)...);
	}
	template<class Component>
	Ref<Component> IActor::find() const
	{
		return m_components.find<Component>();
	}
	template<class Component>
	s3d::Array<Ref<Component>> IActor::finds() const
	{
		return m_components.finds<Component>();
	}
}