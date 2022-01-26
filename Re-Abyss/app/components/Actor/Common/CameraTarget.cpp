#include <abyss/components/Actor/Common/CameraTarget.hpp>

#include <abyss/components/Actor/Common/ILocator.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
namespace abyss::Actor
{
    class CameraTarget::Impl : public CameraTargetBase
    {
    public:
        Impl(CameraTargetPriority priority):
            CameraTargetBase(priority)
        {}
        s3d::Vec2 targetPos() const
        {
            return m_locator->getCenterPos();
        }
        void setLocator(const Ref<ILocator>& locator)
        {
            m_locator = locator;
        }
    private:
        Ref<ILocator> m_locator;
    };
    CameraTarget::CameraTarget(ActorObj* pActor, CameraTargetPriority priority):
        m_pActor(pActor),
        m_target(std::make_shared<Impl>(priority))
    {}
    void CameraTarget::setup(Executer executer)
    {
        executer.on<IComponent>().addAfter<ILocator>();
    }
    void CameraTarget::onStart()
    {
        m_target->setLocator(m_pActor->find<ILocator>());
        m_pActor->getModule<Camera>()->addTarget(m_target);
    }
    void CameraTarget::onEnd()
    {
        m_target->destory();
    }
}
