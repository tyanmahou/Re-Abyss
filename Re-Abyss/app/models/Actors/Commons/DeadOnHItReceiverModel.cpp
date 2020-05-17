#include "DeadOnHItReceiverModel.hpp"
#include <abyss/controllers/Actors/ActInclude.hpp>
#include <abyss/models/Actors/base/IDamageCallbackModel.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>
namespace abyss
{
    DeadOnHItReceiverModel::DeadOnHItReceiverModel(IActor* pActor):
        m_pActor(pActor)
    {}
    DeadOnHItReceiverModel& DeadOnHItReceiverModel::setAutoDestroy(bool isAuto)
    {
        m_isAutoDestroy = isAuto;
        return *this;
    }
    void DeadOnHItReceiverModel::onCollisionStay(IActor * col)
    {
        if (m_pActor->isDestroyed()) {
            return;
        }
        col->accept([this](const Receiver&) {
            // 当たって消える
            for (auto&& callback : m_pActor->finds<IDeadCallbackModel>()) {
                callback->onDead();
            }
            if (m_isAutoDestroy) {
                m_pActor->destroy();
            }
        });
    }
}
