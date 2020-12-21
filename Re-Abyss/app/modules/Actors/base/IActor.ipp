#pragma once

namespace abyss::Actor
{
	inline void IActor::setId(s3d::uint64 id)
	{
		m_id = id;
	}

	inline s3d::uint64 IActor::getId() const
	{
		return m_id;
	}
	inline void IActor::setIsDontDestoryOnLoad(bool isDontDestoryOnLoad)
	{
		m_isDontDestoryOnLoad = isDontDestoryOnLoad;
	}
	inline bool IActor::isDontDestoryOnLoad() const
	{
		return m_isDontDestoryOnLoad;
	}

	inline void IActor::setOrder(s3d::int32 order)
	{
		m_order = order;
	}

	inline s3d::int32 IActor::getOrder() const
	{
		return m_order;
	}

	inline void IActor::setTag(const TagType& tag)
	{
		m_tag = tag;
	}

	inline const TagType& IActor::getTag() const
	{
		return m_tag;
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