#pragma once

namespace abyss::Actor
{
	inline void IActor::setManager(Manager* const pManager)
	{
		m_pManager = pManager;
	}
	inline Manager* IActor::getManager() const
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
	inline void IActor::setIsDontDestoryOnLoad(bool isDontDestoryOnLoad)
	{
		m_isDontDestoryOnLoad = isDontDestoryOnLoad;
	}
	inline bool IActor::isDontDestoryOnLoad() const
	{
		return m_isDontDestoryOnLoad;
	}
	inline s3d::int32 IActor::getOrder() const
	{
		return m_order;
	}

	inline const TagType& IActor::getTag() const
	{
		return m_tag;
	}

	inline void IActor::setTag(const TagType& tag)
	{
		m_tag = tag;
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
	Ref<Component> IActor::attach(const std::shared_ptr<Component>& component) const
		requires IsComponent<Component>
	{
		return m_components.add<Component>(component);
	}

	template<class Component, class... Args>
	Ref<Component> IActor::attach(Args&&... args) const
		requires
		IsComponent<Component>&&
		std::constructible_from<Component, Args...>
	{
		return m_components.add<Component>(std::forward<Args>(args)...);
	}

	template<class Component>
	bool IActor::detach() const
		requires IsComponent<Component>
	{
		return m_components.remove<Component>();
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

	template<Tag::Tagged T>
	bool IActor::isThen(std::function<bool(IActor*)> callback)
	{
		if (m_tag.is<T>()) {
			return callback(this);
		}
		return false;
	}
	template<Tag::Tagged T, IsComponent C>
	bool IActor::isThen(std::function<bool(C&)> callback) const
	{
		if (m_tag.is<T>()) {
			if (auto c = this->find<C>()) {
				return callback(*c.get());
			}
		}
		return false;
	}
	template<Tag::Tagged T>
	bool IActor::isNotThen(std::function<bool(IActor*)> callback)
	{
		if (m_tag.isNot<T>()) {
			return callback(this);
		}
		return false;
	}
}