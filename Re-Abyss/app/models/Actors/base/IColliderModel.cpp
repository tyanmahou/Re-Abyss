#include "IColliderModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>

namespace abyss
{
    IColliderModel::IColliderModel(IActor* pActor):
        m_pActor(pActor)
    {}
    IColliderModel& IColliderModel::setTag(const s3d::String& tag)
    {
        m_tag = tag;
        return *this;
    }
    const s3d::String& IColliderModel::getTag() const
    {
        return m_tag;
    }
    IColliderModel& IColliderModel::setLayer(const s3d::String& layer)
    {
        m_layer = layer;
        return *this;
    }
    const s3d::String& IColliderModel::getLayer() const
    {
        return m_layer;
    }
    IColliderModel& IColliderModel::setActive(bool isActive)
    {
        m_isActive = isActive;
        return *this;
    }
    bool IColliderModel::isActive() const
    {
        return m_isActive && m_pActor->isActive();
    }
    s3d::uint64 IColliderModel::getId() const
    {
        return m_pActor->getId();
    }
    void IColliderModel::onReflesh()
    {
        for (auto&& callback : m_pActor->finds<ICollisionCallbackModel>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onReflesh();
        }
    }
    void IColliderModel::onCollisionEnter(IActor* col)
    {
        for (auto&& callback : m_pActor->finds<ICollisionCallbackModel>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionEnter(col);
        }
    }
    void IColliderModel::onCollisionStay(IActor* col)
    {
        for (auto&& callback : m_pActor->finds<ICollisionCallbackModel>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionStay(col);
        }
    }
    void IColliderModel::onCollisionExit(IActor * col)
    {
        for (auto&& callback : m_pActor->finds<ICollisionCallbackModel>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionExit(col);
        }
    }
}
