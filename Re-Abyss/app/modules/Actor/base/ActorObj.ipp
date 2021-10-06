#pragma once

namespace abyss::Actor
{
	inline void ActorObj::setId(s3d::uint64 id)
	{
		m_id = id;
	}

	inline s3d::uint64 ActorObj::getId() const
	{
		return m_id;
	}
	inline void ActorObj::setDestoryTiming(DestoryTiming timing)
	{
		m_destoryTiming = timing;
	}
	inline DestoryTiming ActorObj::getDestoryTiming() const
	{
		return m_destoryTiming;
	}
	inline bool ActorObj::isDestoryCheckIn() const
	{
		return m_destoryTiming == DestoryTiming::CheckIn;
	}
	inline bool ActorObj::isDestoryCheckOut() const
	{
		return m_destoryTiming == DestoryTiming::CheckOut;
	}
	inline bool ActorObj::isDestoryNever() const
	{
		return m_destoryTiming == DestoryTiming::Never;
	}

	inline void ActorObj::setTag(const TagType& tag)
	{
		m_tag = tag;
	}

	inline const TagType& ActorObj::getTag() const
	{
		return m_tag;
	}
	inline void ActorObj::setBufferLayer(BufferLayer layer)
	{
		m_bufferLayer = layer;
	}

	inline BufferLayer ActorObj::getBufferLayer()const
	{
		return m_bufferLayer;
	}

	template<TaggedOf<Tag::ActorTagKind> T>
	bool ActorObj::isThen(std::function<bool(ActorObj*)> callback)
	{
		if (m_tag.is<T>()) {
			return callback(this);
		}
		return false;
	}
	template<TaggedOf<Tag::ActorTagKind> T, IsComponent C>
	bool ActorObj::isThen(std::function<bool(C&)> callback) const
	{
		if (m_tag.is<T>()) {
			if (auto c = this->find<C>()) {
				return callback(*c.get());
			}
		}
		return false;
	}
	template<TaggedOf<Tag::ActorTagKind> T>
	bool ActorObj::isNotThen(std::function<bool(ActorObj*)> callback)
	{
		if (m_tag.isNot<T>()) {
			return callback(this);
		}
		return false;
	}
}