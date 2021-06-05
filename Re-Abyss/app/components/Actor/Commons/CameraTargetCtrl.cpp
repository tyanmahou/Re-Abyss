#include "CameraTargetCtrl.hpp"

#include <abyss/components/Actor/base/ILocator.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
namespace abyss::Actor
{
    class CameraTargetCtrl::CameraTarget : public CameraTargetBase
    {
    public:
        CameraTarget(ActorObj* pActor, CameraTargetPriorityType priority):
            CameraTargetBase(priority),
            m_pActor(pActor)
        {}
        s3d::Vec2 targetPos() const
        {
            return m_locator->getCenterPos();
        }
        void setup(Executer executer)
        {
            executer.on<IComponent>().addAfter<ILocator>();
        }
        void onStart()
        {
            m_locator = m_pActor->find<ILocator>();
        }
        void onEnd()
        {
            this->destory();
        }
        ActorObj* actor() const
        {
            return m_pActor;
        }
    private:
        ActorObj* m_pActor;
        Ref<ILocator> m_locator;
    };
    CameraTargetCtrl::CameraTargetCtrl(ActorObj* pActor, CameraTargetPriorityType priority):
        m_target(std::make_shared<CameraTarget>(pActor, priority))
    {}
    void CameraTargetCtrl::setup(Executer executer)
    {
        m_target->setup(executer);
    }
    void CameraTargetCtrl::onStart()
    {
        m_target->onStart();
        m_target->actor()->getModule<Camera>()->addTarget(m_target);
    }
    void CameraTargetCtrl::onEnd()
    {
        m_target->destory();
    }
}
