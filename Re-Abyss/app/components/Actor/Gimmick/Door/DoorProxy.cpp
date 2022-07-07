#include <abyss/components/Actor/Gimmick/Door/DoorProxy.hpp>

namespace abyss::Actor::Gimmick::Door
{
	DoorProxy::DoorProxy(ActorObj* pActor, const DoorEntity& entity) :
		m_pActor(pActor),
        m_startId(entity.startId),
        m_link(entity.link),
		m_pos(entity.pos),
		m_size(entity.size),
        m_kind(entity.kind)
	{
	}
	CShape DoorProxy::getCollider() const
	{
		return Circle(this->getPos(), 10);
	}
	s3d::int32 DoorProxy::getStartId() const
	{
        return m_startId;
	}
    const s3d::Optional<s3d::String>& DoorProxy::getLink() const
    {
        return m_link;
    }
	void DoorProxy::setup([[maybe_unused]]Executer executer)
	{}
	void DoorProxy::onStart()
	{}

	const s3d::Vec2& DoorProxy::getPos() const
	{
        return m_pos;
	}
    const s3d::Vec2& DoorProxy::getSize() const
    {
        return m_size;
    }
	DoorKind DoorProxy::getKind() const
	{
        return m_kind;
	}
}
