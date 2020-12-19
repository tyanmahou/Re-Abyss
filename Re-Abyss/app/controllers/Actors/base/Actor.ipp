#pragma once

namespace abyss::Actor
{
	inline void Actor::setManager(Manager* const pManager)
	{
		m_pManager = pManager;
	}
	inline Manager* Actor::getManager() const
	{
		return m_pManager;
	}
	inline void Actor::setId(s3d::uint64 id)
	{
		m_id = id;
	}

	inline s3d::uint64 Actor::getId() const
	{
		return m_id;
	}

	inline void Actor::setActive(bool active)
	{
		m_isActive = active;
	}
	inline bool Actor::isActive() const
	{
		return m_isActive;
	}
	inline void Actor::destroy()
	{
		m_isDestroyed = true;
	}
	inline bool Actor::isDestroyed() const
	{
		return m_isDestroyed;
	}
	inline bool Actor::isDontDestoryOnLoad() const
	{
		return m_isDontDestoryOnLoad;
	}
	inline s3d::int32 Actor::getOrder() const
	{
		return m_order;
	}

	inline const TagType& Actor::getTag() const
	{
		return m_tag;
	}

	template<class T>
	T* Actor::getModule() const
	{
		if (!m_pManager) {
			return nullptr;
		}
		return m_pManager->getModule<T>();
	}

	template<class Component>
	Ref<Component> Actor::attach(const std::shared_ptr<Component>& component) const
		requires IsComponent<Component>
	{
		return m_components.add<Component>(component);
	}

	template<class Component, class... Args>
	Ref<Component> Actor::attach(Args&&... args) const
		requires
		IsComponent<Component>&&
		std::constructible_from<Component, Args...>
	{
		return m_components.add<Component>(std::forward<Args>(args)...);
	}

	template<class Component>
	bool Actor::detach() const
		requires IsComponent<Component>
	{
		return m_components.remove<Component>();
	}

	template<class Component>
	Ref<Component> Actor::find() const
	{
		return m_components.find<Component>();
	}
	template<class Component>
	s3d::Array<Ref<Component>> Actor::finds() const
	{
		return m_components.finds<Component>();
	}

	template<Tag::Tagged T>
	bool Actor::isThen(std::function<bool(Actor*)> callback)
	{
		if (m_tag.is<T>()) {
			return callback(this);
		}
		return false;
	}
	template<Tag::Tagged T, IsComponent C>
	bool Actor::isThen(std::function<bool(C&)> callback) const
	{
		if (m_tag.is<T>()) {
			if (auto c = this->find<C>()) {
				return callback(*c.get());
			}
		}
		return false;
	}
	template<Tag::Tagged T>
	bool Actor::isNotThen(std::function<bool(Actor*)> callback)
	{
		if (m_tag.isNot<T>()) {
			return callback(this);
		}
		return false;
	}
}