#include "ICollider.hpp"
#include <abyss/components/Actors/base/ICollisionCallback.hpp>

namespace abyss::Actor
{
    ICollider::ICollider(IActor* pActor):
        m_pActor(pActor)
    {}

    ICollider& ICollider::setLayer(const s3d::String& layer)
    {
        m_layer = layer;
        return *this;
    }
    const s3d::String& ICollider::getLayer() const
    {
        return m_layer;
    }
    ICollider& ICollider::setActive(bool isActive)
    {
        m_isActive = isActive;
        return *this;
    }
    bool ICollider::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }
    s3d::uint64 ICollider::getId() const
    {
        return m_pActor->getId();
    }
    void ICollider::onReflesh()
    {
        for (auto&& callback : m_pActor->finds<ICollisionCallback>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onReflesh();
        }
    }
    void ICollider::onCollisionEnter(ICollider* col)
    {
        for (auto&& callback : m_pActor->finds<ICollisionCallback>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionEnter(col);
        }
    }
    void ICollider::onCollisionStay(ICollider* col)
    {
        for (auto&& callback : m_pActor->finds<ICollisionCallback>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionStay(col);
        }
    }
    void ICollider::onCollisionExit(ICollider* col)
    {
        for (auto&& callback : m_pActor->finds<ICollisionCallback>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionExit(col);
        }
    }
}
