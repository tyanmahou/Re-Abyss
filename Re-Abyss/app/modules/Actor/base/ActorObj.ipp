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

	inline void ActorObj::setBufferLayer(BufferLayer layer)
	{
		m_bufferLayer = layer;
	}

	inline BufferLayer ActorObj::getBufferLayer()const
	{
		return m_bufferLayer;
	}
}