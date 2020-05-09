#include "IColliderModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/base/ICollisionCallbackModel.hpp>
namespace abyss
{
    IColliderModel::IColliderModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void IColliderModel::setTag(const s3d::String& tag)
    {
        m_tag = tag;
    }
    const s3d::String& IColliderModel::getTag() const
    {
        return m_tag;
    }
    void IColliderModel::setLayer(const s3d::String& layer)
    {
        m_layer = layer;
    }
    const s3d::String& IColliderModel::getLayer() const
    {
        return m_layer;
    }
    bool IColliderModel::isActive() const
    {
        return m_pActor->isActive();
    }
    s3d::uint64 IColliderModel::getId() const
    {
        return m_pActor->getId();
    }
    void IColliderModel::onReflesh()
    {
        for (auto&& callback : m_pActor->findComponents<ICollisionCallbackModel>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onReflesh();
        }
    }
    void IColliderModel::onCollisionEnter(IActor* col)
    {
        for (auto&& callback : m_pActor->findComponents<ICollisionCallbackModel>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionEnter(col);
        }
    }
    void IColliderModel::onCollisionStay(IActor* col)
    {
        for (auto&& callback : m_pActor->findComponents<ICollisionCallbackModel>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionStay(col);
        }
    }
    void IColliderModel::onCollisionExit(IActor * col)
    {
        for (auto&& callback : m_pActor->findComponents<ICollisionCallbackModel>()) {
            if (!callback->isActive()) {
                continue;
            }
            callback->onCollisionExit(col);
        }
    }
}
